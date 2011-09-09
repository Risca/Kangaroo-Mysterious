/** ============================================================================
 *  @file   kamy.h
 *
 *  @path   $(DSPLINK)/gpp/src/samples/kamy/
 *
 *  @desc   Defines the interface used for driving the kamy application.
 *
  */


#if !defined (KM_H)
#define KM_H

#include <dsplink.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  @func   KM_Main
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
 *  @arg    strWidth
 *              Width of image in string format.
 *  @arg    width
 *              Width of image in numeric format.
 *  @arg    strHeight
 *              Height of image in string format.
 *  @arg    height
 *              Height of image in numeric format.
 *  @arg    strNumIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in string format.
 *  @arg    numIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in numeric format.
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
KM_Main (IN Char8 * dspExecutable,
           IN Char8 * strDspAddress,
           IN Uint32  dspAddress,
           IN Char8 * strWidth,
           IN Uint32  width,
           IN Char8 * strHeight,
           IN Uint32  height,
           IN Char8 * strNumIterations,
           IN Uint32  numIterations) ;


/** ============================================================================
 *  @func   KM_0Print
 *
 *  @desc   Print a message without any arguments.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\KM_os.c
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
KM_0Print (IN Char8 * str) ;


/** ============================================================================
 *  @func   KM_1Print
 *
 *  @desc   Print a message with one arguments.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\kamy_os.c
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
KM_1Print (IN Char8 * str, IN Uint32 arg) ;


/** ============================================================================
 *  @func   KM_Sleep
 *
 *  @desc   Sleeps for the specified number of microseconds.
 *          This is a OS specific function and is implemented in file:
 *              <GPPOS>\KM_os.c
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
KM_Sleep (IN Uint32 uSec) ;


/** ============================================================================
 *  @func   KM_AllocateBuffer
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
KM_AllocateBuffer (IN Uint32 size, OUT Pvoid * buf) ;


/** ============================================================================
 *  @func   KM_FreeBuffer
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
KM_FreeBuffer (IN OUT Pvoid * buf) ;


/** ============================================================================
 *  @func   KM_OS_init
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
KM_OS_init ( IN Char8 * strWidth, IN Char8 * strHeight ) ;


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
KM_getFrame( Uchar8 **image_ptr ) ;


/** ============================================================================
 *  @func	KM_displayFrame
 *
 *  @desc	Shows a YUV:422 frame on the screen
 *
 *  @modif	None.
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
KM_displayFrame( Uint16 width, Uint16 height, Uchar8 *image_ptr ) ;


/** ============================================================================
 *  @func   KM_OS_exit
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
KM_OS_exit (Void) ;


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
KM_Atoll (Char8 * str) ;

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
KM_ItoA (Char8 * str, int i) ;

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* !defined (KM_H) */

