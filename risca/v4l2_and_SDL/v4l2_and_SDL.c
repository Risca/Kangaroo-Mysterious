#include <stdio.h>
#include <stdlib.h>

#include "v4l2_inc.h"
#include "SDL_inc.h"
#include "defines.h"
#include "conv.h"

extern int fd;

FilterAttrs attrs = {
    NULL,   /* imgIn        */
    NULL,   /* imgOut       */
    WIDTH,  /* width        */
    HEIGHT, /* height       */
    5,      /* kernelSize   */
    0,      /* offset       */
    0,      /* spacing      */
    0       /* orientation  */
};


int main(int argc,char *argv[])
{
    int i, count = 100;

    attrs.imgOut = malloc (sizeof(Uint8)*2*WIDTH*HEIGHT);
    initSDL ();

    if (!open_device ())
        exit (EXIT_FAILURE);
    printf("Opened device\n");

    if (!init_device (WIDTH, HEIGHT))
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

            if (read_frame ((void*)&attrs.imgIn)) {
                BWFilter_func(&attrs);
                displayFrame (attrs.imgOut);
                break;
            }

            /* EAGAIN - continue select loop. */
        }
    }

    stop_capturing ();
    uninit_device ();
    close_device ();

    exit (EXIT_SUCCESS);
    return 0;
}
