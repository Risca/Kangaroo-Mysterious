/** ============================================================================
 *  @file   foo_os.c
 *
 *  @path   $(DSPLINK)/gpp/src/samples/foo/Linux/
 *
 *  @desc   OS specific implementation of functions used by the foo application.
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
#include <foo.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @func   FOO_OS_init
 *
 *  @desc   This function creates a mem pool.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_OS_init(Void)
{
    DSP_STATUS          status = DSP_SOK ;

    return status ;
}


/** ============================================================================
 *  @func   FOO_OS_exit
 *
 *  @desc   This function deletes a mem pool.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_OS_exit(Void)
{
    DSP_STATUS status = DSP_SOK ;

    return status ;
}


/** ============================================================================
 *  @func   FOO_0Print
 *
 *  @desc   Print a message without any arguments.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_0Print (Char8 * str)
{
    printf (str) ;
    fflush (stdout) ;
}


/** ============================================================================
 *  @func   FOO_1Print
 *
 *  @desc   Print a message with one arguments.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_1Print (Char8 * str, Uint32 arg)
{
    printf (str, arg) ;
    fflush (stdout) ;
}

/** ============================================================================
 *  @func   FOO_Sleep
 *
 *  @desc   Sleeps for the specified number of microseconds.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\FOO_os.c
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_Sleep (IN Uint32 uSec)
{
    usleep (uSec) ;
}


/** ============================================================================
 *  @func   FOO_AllocateBuffer
 *
 *  @desc   Allocates a buffer of specified size.
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_AllocateBuffer (IN Uint32 size, OUT Pvoid * buf)
{
    DSP_STATUS status = DSP_SOK ;

    *buf = malloc (size) ;
    if (*buf == NULL) {
        status = DSP_EMEMORY ;
    }

    return status ;
}


/** ============================================================================
 *  @func   FOO_FreeBuffer
 *
 *  @desc   Frees the specified buffer
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_FreeBuffer (IN OUT Pvoid * buf)
{
    free (*buf) ;
    *buf = NULL ;
}


/** ============================================================================
 *  @func   FOO_Atoll
 *
 *  @desc   Converts ascii to long int
 *
 *  @modif  None
 *  ============================================================================
 */
NORMAL_API
Uint32
FOO_Atoll (Char8 * str)
{
     Uint32 val = 0 ;
     val = strtoll (str, NULL, 16) ;
     return val ;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
