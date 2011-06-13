#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <errno.h>

void errno_exit(const char *s)
{
        fprintf (stderr, "%s error %d, %s\n",
                 s, errno, strerror (errno));

        exit (EXIT_FAILURE);
}

int xioctl(int fd,int request,void *arg)
{
        int r;

        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);

        return r;
}

#endif // COMMON_H
