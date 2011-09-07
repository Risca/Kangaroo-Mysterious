/** ============================================================================
 *  @file   main.c
 *
 *  @path   $(DSPLINK)/dsp/src/samples/foo/
 *
 *  @desc   Main function that calls SWI or TSK foo applications based
 *          on the parameter TSK_MODE.
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


/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <log.h>
#include <swi.h>
#include <sys.h>
#include <sio.h>
#include <tsk.h>
#include <gio.h>
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <dsplink.h>
#include <failure.h>

/*  ----------------------------------- Sample Headers              */
#include <foo.h>
#include <tskFoo.h>
#include <foo_config.h>


/** ============================================================================
 *  @const  FILEID
 *
 *  @desc   FILEID is used by SET_FAILURE_REASON macro.
 *  ============================================================================
 */
#define FILEID             FID_APP_C


/** ============================================================================
 *  @name   numTransfers
 *
 *  @desc   Iterations of data transfer to be done by the application.
 *  ============================================================================
 */
Uint32 numTransfers ;


/** ============================================================================
 *  @name   trace
 *
 *  @desc   trace LOG_Obj used to do LOG_printf
 *  ============================================================================
 */
extern LOG_Obj trace;


/** ============================================================================
 *  @func   atol
 *
 *  @desc   Converts character string to long value.
 *
 *  @arg    str
 *              Pointer to character string.
 *
 *  @ret    <integer value>
 *              Converted integer value.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
extern long atol(const char *str);


/** ----------------------------------------------------------------------------
 *  @func   tskFoo
 *
 *  @desc   Task for TSK based TSKFOO application.
 *
 *  @arg    None
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
static Int tskFoo ();


/** ============================================================================
 *  @func   main
 *
 *  @desc   Entry function.
 *
 *  @modif  None
 *  ============================================================================
 */
Void main(Int argc, Char *argv[])
{
    Int            status = SYS_OK ;
    /* TSK based foo application */
    TSK_Handle     tskFooTask ;

    /* Initialize DSP/BIOS LINK. */
    DSPLINK_init () ;

    /* Get the number of transfers to be done by the application */
    numTransfers = atol (argv[0]) ;

    if (status == SYS_OK) {
        /* Creating task for TSKFOO application */
        tskFooTask = TSK_create(tskFoo, NULL, 0);
        if (tskFooTask != NULL) {
            LOG_printf(&trace, "Create TSKFOO: Success\n");
        }
        else {
            status = SYS_EALLOC ;
            SET_FAILURE_REASON (status) ;
            LOG_printf(&trace, "Create TSKFOO: Failed.\n");
            return;
        }
    }

    return;
}


/** ----------------------------------------------------------------------------
 *  @func   tskFoo
 *
 *  @desc   Task for TSK based TSKFOO application.
 *
 *  @modif  None
 *  ----------------------------------------------------------------------------
 */
static Int tskFoo()
{
    Int                     status = SYS_OK;
    TSKFOO_TransferInfo * info;

    /* Create Phase */
    status = TSKFOO_create (&info);

    /* Execute Phase */
    if (status == SYS_OK) {
        status = TSKFOO_execute (info);
        if (status != SYS_OK) {
            SET_FAILURE_REASON(status);
        }
    }

    /* Delete Phase */
    status = TSKFOO_delete (info);
    if (status != SYS_OK) {
        SET_FAILURE_REASON(status);
    }

    return status;
}

