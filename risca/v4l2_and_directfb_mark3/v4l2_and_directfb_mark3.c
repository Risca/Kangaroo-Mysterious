#include <stdio.h>
#include <stdlib.h>

#include "v4l2_inc.h"
#include "directfb_inc.h"

int width      = 640;
int height     = 480;
extern int fd;

int main(int argc,char *argv[])
{
    void * imgPtr = 0;
    int i, count = 100;
    directfb_init(argc,argv);

    if (!open_device ())
        exit (EXIT_FAILURE);
    printf("Opened device\n");

    if (!init_device (width, height))
        exit (EXIT_FAILURE);
    printf("Initialized device\n");

    if (!start_capturing ())
        exit (EXIT_FAILURE);
    printf("Started capturing\n");

    system("sleep 1");

    for (i = 0; i < count; i++) {
        for (;;)
        {
            fd_set fds;
            struct timeval tv;
            int r;

            FD_ZERO (&fds);
            FD_SET (fd, &fds);

            /* Timeout. */
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            r = select (fd + 1, &fds, NULL, NULL, &tv);

            if (-1 == r)
            {
                if (EINTR == errno)
                    continue;

                fprintf (stderr, "select error %d, %s\n",
                         errno, strerror (errno));
                exit (EXIT_FAILURE);
            }

            if (0 == r)
            {
                fprintf (stderr, "select timeout\n");
                exit (EXIT_FAILURE);
            }

            if (read_frame (&imgPtr)) {
                directfb_render(width, height, imgPtr);
                break;
            }

            /* EAGAIN - continue select loop. */
        }
    }

    stop_capturing ();
    uninit_device ();
    close_device ();

    directfb_release();
    printf("DirectFB released\n");

    exit (EXIT_SUCCESS);
    return 0;
}
