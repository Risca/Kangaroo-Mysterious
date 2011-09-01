#include "blend.h"
#include "directfb_inc.h"
#include <stdio.h>

void add_brightness(unsigned char b, void *p)
{
    unsigned char *data=(unsigned char*)p;
    unsigned int i,j;
    for (j=0;j<YUVSRC_H;j++)
    {
        for (i=0;i<YUVSRC_W;i++)
        {
            if (255-*data < b) {
                *data=255;
            } else {
                *data+=b;
            }
            data++;data++;
        }
    }
}

void add_green_tint(void *p)
{
    unsigned char *data=(unsigned char*)p;
    unsigned char green=30;
    unsigned int i,j;
    for (j=0;j<YUVSRC_H;j++)
    {
        for (i=0;i<YUVSRC_W;i++)
        {
            data++;
            if (*data < green) {
                *data=0;
            } else {
                *data-=green;
            }
            data++;
        }
    }

}

