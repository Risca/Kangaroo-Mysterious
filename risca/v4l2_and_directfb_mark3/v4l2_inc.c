#include "v4l2_inc.h"

struct buffer
{
    void *                  start;
    size_t                  length;
};

int                     fd              = -1;
struct buffer *         buffers         = NULL;
static unsigned int     n_buffers       = 0;
char *                  dev_name        = "/dev/video0";

int errno_exit(const char *s)
{
    fprintf (stderr, "%s error %d, %s\n",
             s, errno, strerror (errno));

    return 0 ;
}

int xioctl(int fd,int request,void *arg)
{
        int r;

        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);

        return r;
}

int clamp(double x)
{
    if( x > 255 )
        x = 255;
    else if( x < 0 )
        x = 0;

    return x;
}

int read_frame(void **ptr)
{
    struct v4l2_buffer buf;

    CLEAR (buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl (fd, VIDIOC_DQBUF, &buf))
    {
        switch (errno)
        {
        case EAGAIN:
            return 0;

        case EIO:
            /* Could ignore EIO, see spec. */

            /* fall through */

        default:
            return errno_exit ("VIDIOC_DQBUF");
        }
    }

    assert (buf.index < n_buffers);

    *ptr = buffers[buf.index].start ;

    if (-1 == xioctl (fd, VIDIOC_QBUF, &buf))
        return errno_exit ("VIDIOC_QBUF");
/*
    if (ptr)
        printf("image ready at %lx\n", (unsigned long)ptr);
*/
    return 1;
}

void stop_capturing()
{
    enum v4l2_buf_type type;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == xioctl (fd, VIDIOC_STREAMOFF, &type))
        errno_exit ("VIDIOC_STREAMOFF");
}

int start_capturing()
{
    unsigned int i;
    enum v4l2_buf_type type;

    for (i = 0; i < n_buffers; ++i)
    {
        struct v4l2_buffer buf;

        CLEAR (buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (-1 == xioctl (fd, VIDIOC_QBUF, &buf))
            return errno_exit ("VIDIOC_QBUF");
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == xioctl (fd, VIDIOC_STREAMON, &type))
        return errno_exit ("VIDIOC_STREAMON");

   return 1;
}

void uninit_device()
{
    unsigned int i;

    for (i = 0; i < n_buffers; ++i)
        if (-1 == munmap (buffers[i].start, buffers[i].length))
            errno_exit ("munmap");

    free (buffers);
}

int init_mmap()
{
    struct v4l2_requestbuffers req;

    CLEAR (req);

    req.count               = 4;
    req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory              = V4L2_MEMORY_MMAP;

    if (-1 == xioctl (fd, VIDIOC_REQBUFS, &req))
    {
        if (EINVAL == errno)
        {
            fprintf (stderr, "%s does not support "
                     "memory mapping\n", dev_name);
            return 0;
        }
        else
        {
            return errno_exit ("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2)
    {
        fprintf (stderr, "Insufficient buffer memory on %s\n",
                 dev_name);
        return 0;
    }

    buffers = calloc (req.count, sizeof (*buffers));

    if (!buffers)
    {
        fprintf (stderr, "Out of memory\n");
        return 0;
    }

    for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
        struct v4l2_buffer buf;

        CLEAR (buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = n_buffers;

        if (-1 == xioctl (fd, VIDIOC_QUERYBUF, &buf))
            return errno_exit ("VIDIOC_QUERYBUF");

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start =
            mmap (NULL /* start anywhere */,
                  buf.length,
                  PROT_READ | PROT_WRITE /* required */,
                  MAP_SHARED /* recommended */,
                  fd, buf.m.offset);

        if (MAP_FAILED == buffers[n_buffers].start)
            return errno_exit ("mmap");

        printf("buffer %u allocated with size %u at %lx\n",
               n_buffers, (unsigned int)buffers[n_buffers].length,
               (unsigned long)buffers[n_buffers].start);
        
    }

    return 1;
}

int init_device( unsigned short width, unsigned short height )
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    if (-1 == xioctl (fd, VIDIOC_QUERYCAP, &cap))
    {
        if (EINVAL == errno)
        {
            fprintf (stderr, "%s is no V4L2 device\n",
                     dev_name);
            return 0;
        }
        else
        {
            errno_exit ("VIDIOC_QUERYCAP");
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        fprintf (stderr, "%s is no video capture device\n",
                 dev_name);
        return 0;
    }

    if (!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        fprintf (stderr, "%s does not support streaming i/o\n",
                 dev_name);
        return 0;
    }

    /* Select video input, video standard and tune here. */

    CLEAR (cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
    {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl (fd, VIDIOC_S_CROP, &crop))
        {
            switch (errno)
            {
            case EINVAL:
                /* Cropping not supported. */
                break;
            default:
                /* Errors ignored. */
                break;
            }
        }
    }
    else
    {
        /* Errors ignored. */
    }


    CLEAR (fmt);

    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = width;
    fmt.fmt.pix.height      = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    if (-1 == xioctl (fd, VIDIOC_S_FMT, &fmt))
        return errno_exit ("VIDIOC_S_FMT");

    /* Note VIDIOC_S_FMT may change width and height. */

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    return init_mmap ();
}

void close_device()
{
    if (-1 == close (fd))
        errno_exit ("close");

    fd = -1;
}

int open_device()
{
    struct stat st;

    if (-1 == stat (dev_name, &st))
    {
        fprintf (stderr, "Cannot identify '%s': %d, %s\n",
                 dev_name, errno, strerror (errno));
        return 0;
    }

    if (!S_ISCHR (st.st_mode))
    {
        fprintf (stderr, "%s is no device\n", dev_name);
        return 0;
    }

    fd = open (dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

    if (-1 == fd)
    {
        fprintf (stderr, "Cannot open '%s': %d, %s\n",
                 dev_name, errno, strerror (errno));
        return 0;
    }

    return 1;
}

