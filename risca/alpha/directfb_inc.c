#include "directfb_inc.h"

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;
static int screen_width  = 0;
static int screen_height = 0;
//static IDirectFBFont *font = NULL;
//static char *title = "Kangaroo-Mysterius";

int directfb_init(int argc, char *argv[])
{
    DFBSurfaceDescription dsc;
/*
    DFBFontDescription font_dsc;
    font_dsc.flags = DFDESC_HEIGHT;
    font_dsc.height = 48;
    DFBCHECK (dfb->CreateFont (dfb, "Vera.ttf", &font_dsc, &font));
    DFBCHECK (primary->SetFont(primary, font));
*/
 
    DFBCHECK (DirectFBInit (&argc, &argv));
    DFBCHECK (DirectFBCreate (&dfb));
    DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_NORMAL));
    dsc.flags = DSDESC_CAPS | DSDESC_PIXELFORMAT;
    dsc.caps  = DSCAPS_PRIMARY | DSCAPS_INTERLACED | DSCAPS_FLIPPING; 
    dsc.pixelformat = DSPF_YUY2;
    DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));
    DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
   /* Blank screen */
    DFBCHECK (primary->SetColor (primary, 0x0, 0x0, 0x0, 0xFF));
    DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width, screen_height));
    /* Print text */
    /*
    DFBCHECK (primary->SetColor (primary, 0x80, 0x0, 0x20, 0xFF));
    DFBCHECK (primary->DrawString (primary, title, -1, 10, screen_height-100, DSTF_LEFT));
    */
    /* Flip the front and back buffer, but wait for the vertical retrace to avoid tearing. */
    DFBCHECK (primary->Flip (primary, NULL, DSFLIP_WAITFORSYNC));

/*    font->Release (font); */
    return 23;
}

int directfb_render(const void *p)
{
    DFBRectangle rect = {0,0,YUVSRC_W,YUVSRC_H};
    primary->Write(primary,&rect,p,YUVFRAME_Pitch);
//    DFBCHECK (primary->Flip (primary, NULL, DSFLIP_NONE));
    DFBCHECK (primary->Flip (primary, NULL, DSFLIP_WAITFORSYNC));

    return 0;
}

int directfb_release()
{
    primary->Release(primary);
    dfb->Release(dfb);
    return 0;
}
