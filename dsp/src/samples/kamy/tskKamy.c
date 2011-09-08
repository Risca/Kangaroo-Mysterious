/** ============================================================================
 *  @file   tskKamy.c
 *
 *  @path   $(DSPLINK)/dsp/src/samples/kamy/
 *
 *  @desc   This is simple TSK based application that uses SIO interface to
 *          implement kamy for GPP. It receives data from the a input
 *          channel and send the same data back from output channel. Input and
 *          output channel numbers are configurable through header file of this
 *          application. It also uses a message queue to receive a
 *          scaling factor for the output data.
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
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <failure.h>
#include <dsplink.h>
#include <platform.h>
#include <hal_cache.h>

/*  ----------------------------------- Sample Headers              */
#include <tskKamy.h>
#include <kamy.h>
#include <kamy_config.h>
#include <conv.h>


/** ============================================================================
 *  @const  FILEID
 *
 *  @desc   FILEID is used by SET_FAILURE_REASON macro.
 *  ============================================================================
 */
#define FILEID  FID_APP_C

/** ============================================================================
 *  @name   trace
 *
 *  @desc   trace LOG_Obj used to do LOG_printf
 *  ============================================================================
 */
extern LOG_Obj trace ;

/** ============================================================================
 *  @name   yuvWidth
 *
 *  @desc   Width of YUV image to process
 *  ============================================================================
 */
extern Uint32 yuvWidth ;

/** ============================================================================
 *  @name   yuvHeight
 *
 *  @desc   Height of YUV image to process
 *  ============================================================================
 */
extern Uint32 yuvHeight ;

/** ============================================================================
 *  @name   numTransfers
 *
 *  @desc   Iterations of data transfer to be done by the application.
 *  ============================================================================
 */
extern Uint32 numTransfers ;

/** ============================================================================
 *  @func   TSKKM_create
 *
 *  @desc   Create phase function for the TSKKM application. Initializes the
 *          TSKKM_TransferInfo structure with the information that will be
 *          used by the other phases of the application.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKKM_create(TSKKM_TransferInfo ** infoPtr)
{
    Int                     status    = SYS_OK ;
    MSGQ_Attrs              msgqAttrs = MSGQ_ATTRS ;
    TSKKM_TransferInfo *    info      = NULL ;
    MSGQ_LocateAttrs        syncLocateAttrs ;

    /* Allocate TSKKM_TransferInfo structure that will be initialized
     * and passed to other phases of the application */
    *infoPtr = MEM_calloc (DSPLINK_SEGID,
                           sizeof (TSKKM_TransferInfo),
                           DSPLINK_BUF_ALIGN) ;
    if (*infoPtr == NULL) {
        status = SYS_EALLOC ;
        SET_FAILURE_REASON (status) ;
    }
    else {
        info = *infoPtr ;
    }

    /* The GPP side will be waiting for DSP to open a MSGQ. Open the local
     * MSGQ first.
     */
    if (status == SYS_OK) {
        /* Set the semaphore to a known state. */
        SEM_new (&(info->notifyDspSemObj), 0) ;

        /* Fill in the attributes for this message queue. */
        msgqAttrs.notifyHandle = &(info->notifyDspSemObj) ;
        msgqAttrs.pend         = (MSGQ_Pend) SEM_pendBinary ;
        msgqAttrs.post         = (MSGQ_Post) SEM_postBinary ;

        /* Creating message queue */
        status = MSGQ_open (DSP_MSGQNAME, &info->dspMsgqQueue, &msgqAttrs) ;
        if (status != SYS_OK) {
            SET_FAILURE_REASON (status) ;
        }
    }

    /*  Now locate the GPP message queue  */
    if (status == SYS_OK) {
        /* Synchronous locate. */
        status = SYS_ENOTFOUND ;
        while ((status == SYS_ENOTFOUND) || (status == SYS_ENODEV)) {
            syncLocateAttrs.timeout = SYS_FOREVER ;
            status = MSGQ_locate (GPP_MSGQNAME,
                                  &info->gppMsgqQueue,
                                  &syncLocateAttrs) ;
            if ((status == SYS_ENOTFOUND) || (status == SYS_ENODEV)) {
                TSK_sleep (1000) ;
            }
            else if (status != SYS_OK) {
                LOG_printf (&trace, "MSGQ_locate (msgqOut) failed. "
                            "Status = 0x%x\n", status) ;
            }
        }
    }

    if (status == SYS_OK) {
        /* Filling up the transfer info structure */
        info->numTransfers  = numTransfers ;
        info->width         = yuvWidth ;
        info->height        = yuvHeight ;
    }

    return status ;
}


/** ============================================================================
 *  @func   TSKKM_execute
 *
 *  @desc   Execute phase function for the TSKKM application. Application
 *          receives the data from the input channel and sends the same data
 *          back on output channel. Channel numbers can be configured through
 *          header file.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKKM_execute(TSKKM_TransferInfo * info)
{
    Int             status    = SYS_OK;
    Uint8 *         readBuf ;
    Uint8 *         writeBuf ;
    Uint32          size ;
    Uint32          i;
    SampleMessage * msg;

    /* Execute the loop for configured number of transfers
     * A value of 0 in numTransfers implies infinite iterations
     */
    for (i = 0 ;
         (   ((info->numTransfers == 0) || (i < info->numTransfers))
          && (status == SYS_OK)) ;
         i++) {
        /* Wait for the messaging containing information about data buffer */
        status = MSGQ_get (info->dspMsgqQueue, (MSGQ_Msg *) &msg, SYS_FOREVER) ;
        if (status == SYS_OK) {
            readBuf       = (Uint8 *) msg->gppWriteAddr ;
            writeBuf      = (Uint8 *) msg->dspWriteAddr ;
            size          = msg->size ;

            HAL_cacheInv ((Ptr) readBuf, size) ;

            /* Do DSP stuff here! */
            convimg (readBuf, writeBuf, info->width, info->height, 0);

            HAL_cacheWbInv ((Ptr)(msg->dspWriteAddr), size) ;

            /* Now send a message to the GPP */
            status = MSGQ_put (info->gppMsgqQueue, (MSGQ_Msg) msg) ;
            if (status != SYS_OK) {
                SET_FAILURE_REASON(status);
            }
        }
    }

    return status ;
}


/** ============================================================================
 *  @func   TSKKM_delete
 *
 *  @desc   Delete phase function for the TSKKM application. It deallocates
 *          all the resources of allocated during create phase of the
 *          application.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKKM_delete (TSKKM_TransferInfo * info)
{
    Int         status     = SYS_OK ;
    Bool        freeStatus = FALSE ;

    /* Delete the message queue */
    if (info->dspMsgqQueue != NULL) {
        status = MSGQ_close (info->dspMsgqQueue) ;
        if (status != SYS_OK) {
            SET_FAILURE_REASON (status) ;
        }
    }

    /* Free the info structure */
    freeStatus = MEM_free(DSPLINK_SEGID, info, sizeof (TSKKM_TransferInfo));
    if (freeStatus != TRUE) {
        status = SYS_EFREE;
        SET_FAILURE_REASON(status);
    }

    return status;
}
