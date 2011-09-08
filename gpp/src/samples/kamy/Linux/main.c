/** ============================================================================
 *  @file   main.c
 *
 *  @path   $(DSPLINK)/gpp/src/samples/kamy/Linux/
 *
 *  @desc   Linux specific implementation of kamy sample application's driver.
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

/*  ----------------------------------- DSP/BIOS Link                 */
#include <dsplink.h>

/*  ----------------------------------- Application Header            */
#include <kamy.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

/** ============================================================================
 *  @func   main
 *
 *  @desc   Entry point for the application
 *
 *  @modif  None
 *  ============================================================================
 */
int main (int argc, char ** argv)
{
    Char8 * dspExecutable    = NULL ;
    Char8 * strDspAddress    = NULL ;
	Char8 * strWidth         = NULL ;
	Char8 * strHeight        = NULL ;
    Char8 * strNumIterations = NULL ;
    Uint32  dspAddress       = 0 ;
	Uint32  width            = 0 ;
	Uint32  height           = 0 ;
    Uint32  numIterations    = 0 ;
    Char8 * pEnd             = NULL ;

    if (argc != 6 ) {
        printf ("Usage : %s <absolute path of DSP executable> "
                "<DSP address> <width> <height> <number of transfers>\n"
                "For infinite transfers, "
                "use value of 0 for <number of transfers>\n",
                argv [0]) ;
    }
    else {
		dspExecutable    = argv [1] ;
		strDspAddress    = argv [2] ;
		strWidth         = argv [3] ;
		strHeight        = argv [4] ;
		strNumIterations = argv [5] ;
		dspAddress    = strtoul (strDspAddress, &pEnd, 0) ;
		width         = atoi (strWidth) ;
		height        = atoi (strHeight) ;
		numIterations = atoi (strNumIterations) ;
		KM_Main ( dspExecutable,
				strDspAddress,
				dspAddress,
				strWidth,
				width,
				strHeight,
				height,
				strNumIterations,
				numIterations) ;
    }
    return 0 ;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
