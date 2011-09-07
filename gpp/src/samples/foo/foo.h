/** ============================================================================
 *  @file   foo.h
 *
 *  @path   $(DSPLINK)/gpp/src/samples/foo/
 *
 *  @desc   Defines the interface used for driving the foo application.
 *
  */


#if !defined (FOO_H)
#define FOO_H

#include <dsplink.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @func   FOO_Main
 *
 *  @desc   The OS independent driver function for the sample application.
 *
 *  @arg    dspExecutable
 *              Name of the DSP executable file.
 *  @arg    strDspAddress
 *              DSP address to be used for the PROC_read () and PROC_write APIs
 *              in string format.
 *  @arg    dspAddress
 *              DSP address to be used for the PROC_read () and PROC_write APIs
 *              in numeric format.
 *  @arg    strBufferSize
 *              Buffer size to be used for data-transfer in string format.
 *  @arg    bufferSize
 *              Buffer size to be used for data-transfer in numeric format.
 *  @arg    strNumIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in string format.
 *  @arg    numIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in numeric format.
 *  @arg    processorId
 *             Id of the DSP Processor. 
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None.
 *  ============================================================================
 */
NORMAL_API
Void
FOO_Main (IN Char8 * dspExecutable,
           IN Char8 * strDspAddress,
           IN Uint32  dspAddress,
           IN Char8 * strBufferSize,
           IN Uint32  bufferSize,
           IN Char8 * strNumIterations,
           IN Uint32  numIterations,
           IN Uint8   processorId) ;

/** ============================================================================
 *  @func   FOO_0Print
 *
 *  @desc   Print a message without any arguments.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\FOO_os.c
 *
 *  @arg    str
 *              String message to be printed.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_0Print (IN Char8 * str) ;


/** ============================================================================
 *  @func   FOO_1Print
 *
 *  @desc   Print a message with one arguments.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\foo_os.c
 *
 *  @arg    str
 *              String message to be printed.
 *  @arg    arg
 *              Argument to be printed.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_1Print (IN Char8 * str, IN Uint32 arg) ;


/** ============================================================================
 *  @func   FOO_Sleep
 *
 *  @desc   Sleeps for the specified number of microseconds.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\FOO_os.c
 *
 *  @arg    uSec
 *              Microseconds to sleep.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_Sleep (IN Uint32 uSec) ;


/** ============================================================================
 *  @func   FOO_AllocateBuffer
 *
 *  @desc   Allocates a buffer of specified size.
 *
 *  @arg    size
 *              Size of buffer to be allocated
 *  @arg    buf
 *              Placeholder for returning the buffer
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EMEMORY
 *              Memory error occurred.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_AllocateBuffer (IN Uint32 size, OUT Pvoid * buf) ;


/** ============================================================================
 *  @func   FOO_FreeBuffer
 *
 *  @desc   Free the specified buffer.
 *
 *  @arg    buf
 *              Pointer to buffer to be freed.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
Void
FOO_FreeBuffer (IN OUT Pvoid * buf) ;


/** ============================================================================
 *  @func   FOO_OS_init
 *
 *  @desc   This function initializes the OS specific component.
 *
 *  @arg    None
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              General failure.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_OS_init (Void) ;


/** ============================================================================
 *  @func   FOO_OS_exit
 *
 *  @desc   This function finalizes the OS specific component.
 *
 *  @arg    None
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              General failure.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
FOO_OS_exit (Void) ;


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
FOO_Atoll (Char8 * str) ;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* !defined (FOO_H) */

