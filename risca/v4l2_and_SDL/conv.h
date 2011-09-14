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
typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define BORDER		    2
#define MACROPIXEL_SIZE 4
#define SYS_OK          0

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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CONV_H_ */
