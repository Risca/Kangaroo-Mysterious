#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>             /* getopt_long() */

#include "v4l2_inc.h"
//#include "common.h"
#include "directfb_inc.h"

char *dev_name = NULL;
io_method io = IO_METHOD_MMAP;

const char short_options [] = "d:hmru";

const struct option long_options [] =
{
    { "device",     required_argument,      NULL,           'd' },
    { "help",       no_argument,            NULL,           'h' },
    { "mmap",       no_argument,            NULL,           'm' },
    { "read",       no_argument,            NULL,           'r' },
    { "userp",      no_argument,            NULL,           'u' },
    { 0, 0, 0, 0 }
};

void usage(FILE *fp,int argc,char **argv)
{
    fprintf (fp,
             "Usage: %s [options]\n\n"
             "Options:\n"
             "-d | --device name   Video device name [/dev/video]\n"
             "-h | --help          Print this message\n"
             "-m | --mmap          Use memory mapped buffers\n"
             "-r | --read          Use read() calls\n"
             "-u | --userp         Use application allocated buffers\n"
             "",
             argv[0]);
}

int main(int argc,char *argv[])
{
    directfb_init(argc,argv);

    dev_name = "/dev/video0";

    while (1)
    {
        int index;
        int c;

        c = getopt_long (argc, argv,
                         short_options, long_options,
                         &index);

        if (-1 == c)
            break;

        switch (c)
        {
        case 0: /* getopt_long() flag */
            break;

        case 'd':
            dev_name = optarg;
            break;

        case 'h':
            usage (stdout, argc, argv);
            exit (EXIT_SUCCESS);

        case 'm':
            io = IO_METHOD_MMAP;
            break;

        case 'r':
            io = IO_METHOD_READ;
            break;

        case 'u':
            io = IO_METHOD_USERPTR;
            break;

        default:
            usage (stderr, argc, argv);
            exit (EXIT_FAILURE);
        }
    }

    open_device ();
    printf("Opened device\n");
    init_device ();
    printf("Initialized device\n");
    start_capturing ();
    printf("Started capturing\n");
    system("sleep 1");

    mainloop ();
    printf("\nMainloop done\n");

    stop_capturing ();
    uninit_device ();
    close_device ();
    exit (EXIT_SUCCESS);
    return 0;
}
