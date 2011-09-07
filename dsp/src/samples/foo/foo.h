/** ============================================================================
 *  @file   foo.h
 *
 *  @path   $(DSPLINK)/dsp/src/samples/foo/
 *
 *  @desc   Header file for foo application.
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

#ifndef FOO_
#define FOO_

/*  ----------------------------------- DSP/BIOS Headers            */
#include <msgq.h>

#ifdef __cplusplus
extern "C" {
#endif

/** ============================================================================
 *  @const  FOO_REQUEST_MSGID
 *
 *  @desc   Id to denote a scaling change.
 *  ============================================================================
 */
#define FOO_REQUEST_MSGID   1

/** ============================================================================
 *  @name   SampleMessage
 *
 *  @desc   Structure used to pass the scaling factor from the GPP to the DSP.
 *
 *  @field  msgHeader
 *              Required first field of a message.
 *  @field  gppWriteAddr
 *              DSP Memory address where GPP writes.
 *  @field  dspWriteAddr
 *              DSP Memory address where GPP writes.
 *  @field  size
 *              Size of data written
 *  @field  scalingFactor
 *              Used to scale the output buffer values.
 *  ============================================================================
 */
typedef struct SampleMessage_tag {
    MSGQ_MsgHeader msgHeader     ;
    Uint32         gppWriteAddr  ;
    Uint32         dspWriteAddr  ;
    Uint32         size          ;
    Uint32         scalingFactor ;
    Uint32         foobar        ;
} SampleMessage ;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FOO_ */
