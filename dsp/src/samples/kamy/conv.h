/*
 * conv.h
 *
 *  Created on: Sep 1, 2011
 *      Author: staffan
 */

#ifndef CONV_H_
#define CONV_H_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <filters.h>
// Typedefs
#include <std.h>

#define BORDER		2
#define BYTES_PER_PIXEL 4

// Function prototypes
int bypass_func (FilterAttrs *attrs) ;
int convimg_func (FilterAttrs *attrs) ;
int convBox1D (FilterAttrs *attrs) ;
int convBox2D (FilterAttrs *attrs) ;
int BWFilter_func( FilterAttrs *a ) ;

/** ============================================================================
 *  @func   unsharpenMask
 *
 *  @desc   Filter mask that sharpening by subtracting a blurred image. This 
 *	    function highly depends on convimg and should have the same 
 *	    arguments.
 *	    Note: This version of the function destroys the input image.
 *
 *  @arg    inImg_ptr
 *              Pointer to input image.
 *  @arg    outImg_ptr
 *              Pointer to output image.
 *              in string format.
 *  @arg    img_width
 *              Width of the picture in pixels.
 *  @arg    img_height
 *              Height of the picture in pixels.
 *  @arg    kernel_ptr
 *              Pointer to the kernel.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None.
 *
 *  @author Daniel Josefsson
 *  ============================================================================
 */
//void unsharpenMask( unsigned char* inImg_ptr, unsigned char* outImg_ptr, Uint16 img_width, Uint16 img_height, unsigned char* kernel_ptr );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CONV_H_ */
