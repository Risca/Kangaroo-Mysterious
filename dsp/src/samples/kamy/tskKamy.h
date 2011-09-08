/** ============================================================================
 *  @file   tskKamy.h
 *
 *  @path   $(DSPLINK)/dsp/src/samples/kamy/
 *
 *  @desc   Header file for tskKamy application.
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


#ifndef TSKKM_
#define TSKKM_


/*  ----------------------------------- DSP/BIOS Headers            */
#include <msgq.h>
#include <sem.h>


#ifdef __cplusplus
extern "C" {
#endif



/** ============================================================================
 *  @name   TSKKM_TransferInfo
 *
 *  @desc   Structure used to keep various information needed by various phases
 *          of the application. <tbd>
 *
 *  @field  inputStream
 *              Handle to input stream.
 *  @field  outputStream
 *              Handle to output stream.
 *  @field  msgqQueue
 *              Handle of created message queue.
 *  @field  notifySemObj
 *              Semaphore used for message notification.
 *  @field  numTransfers
 *              Number of transfers to be done.
 *  @field  bufferSize
 *              Buffer size information.
 *  @field  receivedSize
 *              Actual length of the buffer that was received.
 *  @field  numBuffers
 *              Number of valid buffers in "buffer" field.
 *  @field  buffer
 *              Buffer pointer.
 *  @field  scalingFactor
 *              Used to kamy the output buffer values.
 *  ============================================================================
 */
typedef struct TSKKM_TransferInfo_tag {
    MSGQ_Queue  gppMsgqQueue ;
    MSGQ_Queue  dspMsgqQueue ;
    SEM_Obj     notifyDspSemObj ;
    Uint32      numTransfers ;
    Uint32      bufferSize ;
    Uint32      scalingFactor ;
    Uint32      kamybar ;
} TSKKM_TransferInfo ;


/** ============================================================================
 *  @func   TSKKM_create
 *
 *  @desc   Create phase function of TSKKM application.
 *
 *  @arg    transferInfo
 *              Information for transfer.
 *
 *  @ret    SYS_OK
 *              Successful operation.
 *          SYS_EBADIO
 *              Failure occured while doing IO.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
Int TSKKM_create (TSKKM_TransferInfo ** transferInfo);

/** ============================================================================
 *  @func   TSKKM_execute
 *
 *  @desc   Excecute phase function of TSKKM application.
 *
 *  @arg    transferInfo
 *              Information for transfer.
 *
 *  @ret    SYS_OK
 *              Successful operation.
 *          SYS_EBADIO
 *              Failure occured while doing IO.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
Int TSKKM_execute (TSKKM_TransferInfo * transferInfo);

/** ============================================================================
 *  @func   TSKKM_delete
 *
 *  @desc   Delete phase function of TSKKM application.
 *
 *  @arg    transferInfo
 *              Information for transfer.
 *
 *  @ret    SYS_OK
 *              Successful operation.
 *          SYS_EBADIO
 *              Failure occured while doing IO.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
Int TSKKM_delete (TSKKM_TransferInfo * transferInfo);


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* TSKKM_ */
