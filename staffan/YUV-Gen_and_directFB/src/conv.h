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

#define IMG_WIDTH 	640
#define IMG_HEIGHT 	480



// Function prototypes
void conv_helloWorld();

/*
 * Convolves an image with a filter kernel. Currently only returns the image unchanged
 */

unsigned char* convimg( unsigned char* image_ptr, unsigned char* kernel_ptr);

/*
 * Generates a YUV:422 image with black and white color gradients. Remember to free the image
 * memory when you are done with it.
 */
unsigned char* gengrad( uint16 width, uint16 height );
unsigned char* genbars( uint16 width, uint16 height );


#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CONV_H_ */
