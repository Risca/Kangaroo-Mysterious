#ifndef V4L2_INC_H
#define V4L2_INC_H

/*
 *  V4L2 video capture example
 *
 *  This program can be used and distributed without restrictions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>

#include "directfb_inc.h"

#define CLEAR(x) memset (&(x), 0, sizeof (x))

typedef enum {
        IO_METHOD_READ,
        IO_METHOD_MMAP,
        IO_METHOD_USERPTR,
} io_method;

extern char *           dev_name;
extern io_method        io;

int clamp(double x);
void process_image(void *p);
int read_frame();
void mainloop();
void stop_capturing();
void start_capturing();
void uninit_device();
void init_read(unsigned int buffer_size);
void init_mmap();
void init_userp(unsigned int buffer_size);
void init_device();
void close_device();
void open_device();

#endif // V4L2_INC_H
