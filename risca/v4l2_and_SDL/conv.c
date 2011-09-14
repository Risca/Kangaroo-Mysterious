/*
 * conv.c
 *
 *  Created on: Sep 1, 2011
 *      Author: staffan
 */
#include <stdio.h>
#include "conv.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int convBox1D (FilterAttrs * attrs)
{
    unsigned int outer = 0, inner = 0, nextPixelOuter, nextPixelInner, maxOuter, indexOffsetOuter, indexOffsetInner, maxInner, convSum, kernelSideWidth;

    Uint8 * offsetImgPtr = attrs->imgIn + attrs->offset;
    kernelSideWidth = (attrs->kernelSize - 1)/2;

    // attrs->orientation = 1 represents vertical and = 0 horizontal.
    if ( attrs->orientation )
    {
        nextPixelOuter = attrs->spacing;
    	nextPixelInner = attrs->width*MACROPIXEL_SIZE;
    	maxOuter = nextPixelInner;
    	maxInner = attrs->height;
    }
    else
    {
        nextPixelOuter = attrs->width*MACROPIXEL_SIZE;
        nextPixelInner = attrs->spacing;
        maxOuter = attrs->height;
    	maxInner = nextPixelOuter;
    }
    for ( outer=0; outer*nextPixelOuter < maxOuter; outer++ )
    {
        indexOffsetOuter = outer*nextPixelOuter;
    	// Reset and preload convSum with the values of the pixels that the inner loop cant handle.
        convSum = 0;
        // Following loads all exept the last convolution values used in the first convolution process.
        // Convolution values that preceds the index = 0 and therefore are out of range will be set to the border value.
        // +1 since one value will be removed in the convolution loop.
    	convSum += offsetImgPtr[ indexOffsetOuter ] * ( kernelSideWidth + 1);
    	for ( inner = 0; inner < kernelSideWidth; inner++ )
    	{
    		convSum += offsetImgPtr[ indexOffsetOuter + inner*nextPixelInner ];
    	}
    	// Start the convolution process.
    	for ( inner = 0; inner*nextPixelInner < maxInner; inner++ )
    	{
            indexOffsetInner = inner*nextPixelInner;
    	    // Check if the last pixel used in the convolution is outside the the range.
    	    if ( nextPixelInner*( inner + kernelSideWidth ) < maxInner )
    	    {
    	        convSum += offsetImgPtr[ indexOffsetOuter + nextPixelInner*( inner + kernelSideWidth ) ];
    	    }
    	    else
    	    {
    	        // Add the max border value.
    	    	convSum += offsetImgPtr[ indexOffsetOuter + maxInner - nextPixelInner ];
    	    }
    	    // Remove the convolution value that not shall be included in this convolution but were in the last.
    	    // Check if the value is out of range
    	    if ( inner <= kernelSideWidth )
    	    {
    	        // Remove the min border value.
    	    	convSum -= offsetImgPtr[ indexOffsetOuter ];
    	    }
    	    else
    	    {
    	        convSum -= offsetImgPtr[ indexOffsetOuter + nextPixelInner*( inner - kernelSideWidth - 1) ];
    	    }
    	    // Store the value.
    	    offsetImgPtr [ indexOffsetOuter + indexOffsetInner ] = convSum/attrs->kernelSize;
    	}
    }
    memcpy(attrs->imgOut, attrs->imgIn, attrs->height * attrs->width *2) ;
    return SYS_OK;
}

int BWFilter_func( FilterAttrs *a )
{
	Uint8 *inImg  = a->imgIn;
	Uint8 *outImg = a->imgOut;
	Uint16 col, row;
	//memcpy(a->imgOut, a->imgIn, width*2*height);

	// Loop through rows.
	for( row = 0; row < a->height; row++)
	{
		// Loop through columns
		for( col = 0; col < a->width; col++)
		{
			*outImg++ = *inImg++;	// Copy Y
			*outImg++ = 128;		// Cr/Cb = 128
			inImg++;
		}
	}
	return SYS_OK;
}
