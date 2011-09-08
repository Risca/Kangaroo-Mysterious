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
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned short int uint16;
typedef short int int16;

//#define IMG_WIDTH 	640
//#define IMG_HEIGHT 	480

#define KERNEL_SIZE	5
#define KERN_MAX_INDEX (KERNEL_SIZE-1)/2
#define BORDER		2


// Function prototypes

/*
 * Convolves an image with a filter kernel. Currently blurs the image.
 */
void convimg(unsigned char* inImg_ptr, unsigned char* outImg_ptr, uint16 img_width, uint16 img_height, unsigned char* kernel_ptr);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CONV_H_ */
