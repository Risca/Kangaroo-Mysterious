#include "v4l2_inc.h"

struct buffer
{
    void *                  start;
    size_t                  length;
};

int                     fd              = -1;
struct buffer *         buffers         = NULL;
static unsigned int     n_buffers       = 0;
static char *           dev_name        = "/dev/video0";

int xioctl(int fd,int request,void *arg)
{
        int r;

        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);

        return r;
}

int read_frame(void *ptr)
{
    struct v4l2_buffer buf;
    unsigned int i;

    CLEAR (buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_USERPTR;

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
            fprintf(stderr, "VIDIOC_DQBUF error %d, %s\n", errno, strerror(errno));
            return 0;
        }
    }

    for (i = 0; i < n_buffers; ++i)
        if (buf.m.userptr == (unsigned long) buffers[i].start
                && buf.length == buffers[i].length)
            break;

    assert (i < n_buffers);

    ptr = (void *) buf.m.userptr;

    if (-1 == xioctl (fd, VIDIOC_QBUF, &buf)) {
        fprintf(stderr, "VIDIOC_QBUF error %d, %s\n", errno, strerror(errno));
        return 0;
    }

    return 1;
}

void stop_capturing()
{
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl (fd, VIDIOC_STREAMOFF, &type))
        fprintf(stderr, "VIDIOC_STREAMOFF error %d, %s\n", errno, strerror(errno));
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
        buf.memory      = V4L2_MEMORY_USERPTR;
        buf.index       = i;
        buf.m.userptr   = (unsigned long) buffers[i].start;
        buf.length      = buffers[i].length;

        if (-1 == xioctl (fd, VIDIOC_QBUF, &buf)) {
            fprintf(stderr, "VIDIOC_QBUF error %d, %s\n", errno, strerror(errno));
            return 0;
        }
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == xioctl (fd, VIDIOC_STREAMON, &type)) {
        fprintf(stderr, "VIDIOC_STREAMON error %d, %s\n", errno, strerror(errno));
        return 0;
    }

    return 1;
}

void uninit_device()
{
    unsigned int i;

    for (i = 0; i < n_buffers; ++i)
        free (buffers[i].start);

    free (buffers);
}

int init_userp(unsigned int buffer_size)
{
    struct v4l2_requestbuffers req;
    unsigned int page_size;

    page_size = getpagesize ();
    buffer_size = (buffer_size + page_size - 1) & ~(page_size - 1);

    CLEAR (req);

    req.count               = 4;
    req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory              = V4L2_MEMORY_USERPTR;

    if (-1 == xioctl (fd, VIDIOC_REQBUFS, &req))
    {
        if (EINVAL == errno)
        {
            fprintf (stderr, "%s does not support "
                     "user pointer i/o\n", dev_name);
            return 0;
        }
        else
        {
            fprintf(stderr,"VIDIOC_REQBUFS error %d, %s\n", errno, strerror(errno));
            return 0;
        }
    }

    buffers = calloc (4, sizeof (*buffers));

    if (!buffers)
    {
        fprintf (stderr, "Out of memory\n");
        return 0;
    }

    for (n_buffers = 0; n_buffers < 4; ++n_buffers)
    {
        buffers[n_buffers].length = buffer_size;
        buffers[n_buffers].start = memalign (/* boundary */ page_size,
                                   buffer_size);

        if (!buffers[n_buffers].start)
        {
            fprintf (stderr, "Out of memory\n");
            return 0;
        }
    }

    return 1;
}

int init_device( unsigned short width, unsigned short height)
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
        }
        else
        {
            fprintf(stderr, "VIDIOC_QUERYCAP error %d, %s\n", errno, strerror(errno));
        }
        return 0;
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
    fmt.fmt.pix.width       = 320;
    fmt.fmt.pix.height      = 240;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    if (-1 == xioctl (fd, VIDIOC_S_FMT, &fmt)) {
        fprintf(stderr, "VIDIOC_S_FMT error %d, %s\n", errno, strerror(errno));
        return 0;
    }

    /* Note VIDIOC_S_FMT may change width and height. */

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    return init_userp (fmt.fmt.pix.sizeimage);
}

void close_device()
{
    if (-1 == close (fd))
        fprintf(stderr, "close error %d, %s\n", errno, strerror(errno));
    /* Errors ignored */

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
