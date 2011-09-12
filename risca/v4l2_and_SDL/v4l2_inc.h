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

#define CLEAR(x) memset (&(x), 0, sizeof (x))
extern int fd;

int read_frame(void **ptr);
void stop_capturing();
int start_capturing();
void uninit_device();
int init_mmap();
int init_device( unsigned short width, unsigned short height );
void close_device();
int open_device();

#endif // V4L2_INC_H
