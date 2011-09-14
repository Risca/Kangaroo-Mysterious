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

//#include "filters.h"
// Typedefs
//#include <std.h>

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef short Int16;
typedef unsigned int Uint32;

#define BORDER		2
#define MACROPIXEL_SIZE 4
#define BYTES_PER_PIXEL 2
#define SYS_OK 0

typedef struct FilterAttrs_tag {
    Uint8 *  imgIn       ;
    Uint8 *  imgOut      ;
    Uint16   width       ;
    Uint16   height      ;
    Uint16   kernelSize  ;
    Uint16   offset      ;
    Uint16   spacing     ;
    Uint16   orientation ;
} FilterAttrs;

// Function prototypes
int bypass_func (FilterAttrs *attrs) ;
int convimg_func (FilterAttrs *attrs) ;
int convBox1D (FilterAttrs *attrs) ;
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
