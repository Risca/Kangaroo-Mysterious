/** ============================================================================
 *  @file   kamy_os.c
 *
 *  @path   $(DSPLINK)/gpp/src/samples/kamy/Linux/
 *
 *  @desc   OS specific implementation of functions used by the kamy application.
 *
 *  @ver    1.65.00.03
 *  ============================================================================
 *  Copyright (C) 2002-2009, Texas Instruments Incorporated -
 *  http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  ============================================================================
 */


/*  ----------------------------------- OS Specific Headers           */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

/*  ----------------------------------- DSP/BIOS Link                 */
#include <dsplink.h>

/*  ----------------------------------- Application Header            */
#include <kamy.h>
#include <directfb_inc.h>
#include <v4l2_inc.h>
#include <conv.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

/* extern int fd;*/

/* ============================================================================
 *  @func   KM_OS_init
 *
 *  @desc   This function creates a mem pool.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_OS_init( Char8 * strWidth, Char8 * strHeight )
{
    KM_0Print ("Entered KM_OS_init ()\n") ;
    DSP_STATUS          status = DSP_SOK ;

    /* Init direct FB */
    directfb_init(0, NULL) ;
    printf("DirectFB initialized\n");

    /* Open camera device (/dev/video0) */
    if (open_device () == 0)
        status = DSP_EFAIL ;

    /* Initialize device */
    if (status == DSP_SOK && 
        init_device ( atoi(strWidth), atoi(strHeight) ) == 0)
        status=DSP_EFAIL ;

    /* Start capturing */
    if (status == DSP_SOK && 
        start_capturing () == 0)
        status = DSP_EFAIL ;

    KM_0Print ("Leaving KM_OS_init ()\n") ;
    return status ;
}


/** ============================================================================
 *  @func	KM_getFrame
 *
 *  @desc	Reads a YUV:422 frame from first available camera
 *
 *  @modif	None.
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_getFrame( Uint8 **image_ptr )
{
    DSP_STATUS          status = DSP_SOK ;

    fd_set fds;
    struct timeval tv;
    int r;
    Uint8 * ptr = 0 ;

    for (;;)
    {
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

            status = DSP_EFAIL ;
            break;
        }

        if (0 == r)
        {
            fprintf (stderr, "select timeout\n");
            status = DSP_EFAIL ;
            break;
        }

        /* Change ptr to point to next frame */
        if (read_frame ((void**)&ptr))
            break;

        /* EAGAIN - continue select loop. */
    }

    /* Update pointer address */
    *image_ptr = ptr;

    return status;
}


/** ============================================================================
 *  @func	KM_displayFrame
 *
 *  @desc	Shows a YUV:422 image on the screen
 *
 *  @modif	None.
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_displayFrame( Uint16 width, Uint16 height, Uchar8 *image_ptr )
{
    DSP_STATUS          status = DSP_SOK ;
   	directfb_render(width, height, image_ptr);
	return status ;
}


/** ============================================================================
 *  @func   KM_OS_exit
 *
 *  @desc   This function deletes a mem pool.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_OS_exit(Void)
{
    DSP_STATUS status = DSP_SOK ;

    /*
    Char8 c = 0 ;
    printf("Press enter to exit\n");
    c = getchar() ;
    while (c != '\n')
            c = getchar() ;
    */
    
    directfb_release() ;

    /* No error checking... yet! */
    stop_capturing () ;
    uninit_device () ;
    close_device () ;

    return status ;
}


/** ============================================================================
 *  @func   KM_0Print
 *
 *  @desc   Print a message without any arguments.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
KM_0Print (Char8 * str)
{
    printf (str) ;
    fflush (stdout) ;
}


/** ============================================================================
 *  @func   KM_1Print
 *
 *  @desc   Print a message with one arguments.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
KM_1Print (Char8 * str, Uint32 arg)
{
    printf (str, arg) ;
    fflush (stdout) ;
}

/** ============================================================================
 *  @func   KM_Sleep
 *
 *  @desc   Sleeps for the specified number of microseconds.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\KM_os.c
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
KM_Sleep (IN Uint32 uSec)
{
    usleep (uSec) ;
}


/** ============================================================================
 *  @func   KM_AllocateBuffer
 *
 *  @desc   Allocates a buffer of specified size.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_AllocateBuffer (IN Uint32 size, OUT Pvoid * buf)
{
    DSP_STATUS status = DSP_SOK ;

    *buf = malloc (size) ;
    if (*buf == NULL) {
        status = DSP_EMEMORY ;
    }

    return status ;
}


/** ============================================================================
 *  @func   KM_FreeBuffer
 *
 *  @desc   Frees the specified buffer
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
KM_FreeBuffer (IN OUT Pvoid * buf)
{
    free (*buf) ;
    *buf = NULL ;
}


/** ============================================================================
 *  @func   KM_Atoll
 *
 *  @desc   Converts ascii to long int
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Uint32
KM_Atoll (Char8 * str)
{
     Uint32 val = 0 ;
     val = strtoll (str, NULL, 16) ;
     return val ;
}

/** ============================================================================
 *  @func   KM_Itoa
 *
 *  @desc   Converts int to ASCII
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
void
KM_ItoA (Char8 * str, int i)
{
    sprintf(str,"%d",i);
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
