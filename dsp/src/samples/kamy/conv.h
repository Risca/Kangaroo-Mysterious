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

// Typedefs
#include <std.h>

//#define IMG_WIDTH 	640
//#define IMG_HEIGHT 	480

#define KERNEL_SIZE	1
#define KERN_MAX_INDEX (KERNEL_SIZE-1)/2
#define BORDER		2

/** ============================================================================
 *  @name   ImageAttrs
 *
 *  @desc   Structure used to pass image attributes to filter functions
 *
 *  @field  img
 *              Pointer to image
 *  @field  width
 *              Width of image
 *  @field  height
 *              Height of image
 *  @field  kernelSize
 *              Size of filter kernel
 *  @field  offset
 *              Offset to first byte to work with in image
 *  @field  spacing
 *              Length between bytes to work with
 *  @field  orientation
 *              0 == horizontal, 1 == vertical
 *  ============================================================================
 */
typedef struct ImageAttrs_tag {
    Uint8 *  img         ;
    Uint16   width       ;
    Uint16   height      ;
    Uint16   kernelSize  ;
    Uint16   offset      ;
    Uint16   spacing     ;
    Uint16   orientation ;
} ImageAttrs ;

/** ============================================================================
 *  @name   KM_Filter
 *
 *  @desc   Prototupe for filter functions
 *  ============================================================================
 */
typedef int (*KM_Filter)(ImageAttrs*) ;

/** ============================================================================
 *  @name   KM_Filters
 *
 *  @desc   Array of KM_Filter function (pointers)
 *  ============================================================================
 */
extern KM_Filter KM_Filters [] ;

// Function prototypes
int dummy(ImageAttrs *attrs);

/*
 * Convolves an image with a filter kernel. Currently blurs the image.
 */
void convimg(unsigned char* inImg_ptr, unsigned char* outImg_ptr, Uint16 img_width, Uint16 img_height, unsigned char* kernel_ptr);

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
void unsharpenMask( unsigned char* inImg_ptr, unsigned char* outImg_ptr, Uint16 img_width, Uint16 img_height, unsigned char* kernel_ptr );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CONV_H_ */
