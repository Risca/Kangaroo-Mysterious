#include <stdio.h>
#include <stdlib.h>

#include "v4l2_inc.h"
#include "directfb_inc.h"

char *dev_name = NULL;
int width      = 640;
int height     = 480;

int main(int argc,char *argv[])
{
    void * imgPtr = 0;
    char c = 0;
    directfb_init(argc,argv);

    dev_name = "/dev/video0";

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

    if (!read_frame(imgPtr))
        exit (EXIT_FAILURE);

    directfb_render(width, height, imgPtr);

    printf("Press enter to continue");
    while ( c != '\n' )
        c = getchar();

    directfb_release();
    printf("DirectFB released\n");

    stop_capturing ();
    uninit_device ();
    close_device ();
    exit (EXIT_SUCCESS);
    return 0;
}
