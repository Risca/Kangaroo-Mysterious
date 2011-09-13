/** ============================================================================
 *  @file   kamy_config.h
 *
 *  @path   $(DSPLINK)/dsp/src/samples/kamy/
 *
 *  @desc   Header file containing configuration for the KM sample.
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


#if !defined (SCALE_CONFIG_)
#define SCALE_CONFIG_


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @const  APP_MSG_SIZE
 *
 *  @desc   Messaging buffer used by the application.
 *  ============================================================================
 */
#define APP_MSG_SIZE (DSPLINK_ALIGN (sizeof (SampleMessage), DSPLINK_BUF_ALIGN))

/** ============================================================================
 *  @const  MAX_BUFFERS
 *
 *  @desc   Size of buffers array.
 *  ============================================================================
 */
#define MAX_BUFFERS        100

/** ============================================================================
 *  @name   SAMPLE_POOL_ID
 *
 *  @desc   ID of the pool used for the sample.
 *  ============================================================================
 */
#define SAMPLE_POOL_ID     0

/** ============================================================================
 *  @const  DSP_MSGQNAME
 *
 *  @desc   Name of the message queue on the DSP.
 *  ============================================================================
 */
#define DSP_MSGQNAME       "DSPMSGQ1"

/** ============================================================================
 *  @const  GPP_MSGQNAME
 *
 *  @desc   Name of the message queue on the GPP.
 *  ============================================================================
 */
#define GPP_MSGQNAME       "GPPMSGQ1"

#if defined (PCPY_LINK)
/** ============================================================================
 *  @name   NUM_BUF_SIZES
 *
 *  @desc   Number of buffer pools to be configured for the allocator.
 *  ============================================================================
 */
#define NUM_BUF_SIZES       2

/** ============================================================================
 *  @const  NUM_BUF_POOL0
 *
 *  @desc   Number of buffers in first buffer pool.
 *  ============================================================================
 */
#define NUM_BUF_POOL0       4

/** ============================================================================
 *  @const  NUM_BUF_POOL1
 *
 *  @desc   Number of buffers in second buffer pool.
 *  ============================================================================
 */
#define NUM_BUF_POOL1       4

/** ============================================================================
 *  @name   SAMPLEPOOL_open
 *
 *  @desc   Macro over the allocator for opening a pool.
 *
 *  @arg    poolId
 *              Pool id.
 *
 *  @see    SAMPLEPOOL_close
 *  ============================================================================
 */
#define SAMPLEPOOL_open(poolId, params)                        \
        (((POOL->allocators [poolId]).fxns->open)              \
                (&(POOL->allocators [poolId].object),          \
                 params))


/** ============================================================================
 *  @name   SAMPLEPOOL_close
 *
 *  @desc   Macro over the allocator for closing a pool.
 *
 *  @arg    poolId
 *              Pool id.
 *
 *  @see    SAMPLEPOOL_open
 *  ============================================================================
 */
#define SAMPLEPOOL_close(poolId)                         \
        (((POOL->allocators [poolId]).fxns->close)       \
                (POOL->allocators [poolId].object))

/** ============================================================================
 *  @name   POOL
 *
 *  @desc   Configuration variable defined by the POOL component.
 *  ============================================================================
 */
extern POOL_Config  * POOL ;

/** ============================================================================
 *  @name   KM_Pools
 *
 *  @desc   Array of pools.
 *  ============================================================================
 */
extern POOL_Obj KM_Pools [] ;
#endif /* if defined (PCPY_LINK) */


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* !defined (SCALE_CONFIG_) */
