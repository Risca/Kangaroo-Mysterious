#include <stdio.h>
#include <unistd.h>

#include <directfb.h>

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;
static int screen_width  = 0;
static int screen_height = 0;
#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

static IDirectFBSurface *logo = NULL;

int main (int argc, char **argv)
{
  int i;
  DFBSurfaceDescription dsc;
  IDirectFBImageProvider *provider;

  DFBCHECK (DirectFBInit (&argc, &argv));
  DFBCHECK (DirectFBCreate (&dfb));
  DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));
  dsc.flags = DSDESC_CAPS;
  dsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));
  DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
  DFBCHECK (dfb->CreateImageProvider (dfb, "dfblogo.png", &provider));
  DFBCHECK (provider->GetSurfaceDescription (provider, &dsc));
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &logo ));
  DFBCHECK (provider->RenderTo (provider, logo, NULL));
  provider->Release (provider);

  for (i = -dsc.width; i < screen_width; i++)
    {
      DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width, screen_height));
      DFBCHECK (primary->Blit (primary, logo, NULL, i, (screen_height - dsc.height) / 2));
      DFBCHECK (primary->Flip (primary, NULL, DSFLIP_WAITFORSYNC));
    }

  logo->Release (logo);
  primary->Release (primary);
  dfb->Release (dfb);

  return 23;
}

