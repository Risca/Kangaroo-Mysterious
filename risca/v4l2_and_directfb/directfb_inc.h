#ifndef DIRECTFB_INC_H
#define DIRECTFB_INC_H

#include <stdio.h>
#include <unistd.h>
#include <directfb.h>

#define YUVSRC_W 640
#define YUVSRC_H 480

#define YUVFRAME_BYTESPerPixel 2
#define YUVFRAME_SIZE (YUVSRC_W * YUVSRC_H)
#define YUVFRAME_Pitch (YUVSRC_W * YUVFRAME_BYTESPerPixel)

#define DFBCHECK(x...)                                             \
{                                                                  \
    DFBResult err = x;                                             \
                                                                   \
    if (err != DFB_OK)                                             \
        {                                                          \
            fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
            DirectFBErrorFatal( #x, err );                         \
        }                                                          \
}

int directfb_init(int argc, char *argv[]);
int directfb_render(const void *p);

#endif // DIRECTFB_INC_H
