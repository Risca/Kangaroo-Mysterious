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
/*  ----------------------------------- DSP/BIOS Headers            */
#include <sys.h>

int bypass_func (FilterAttrs *attrs)
{
    /* I am a dummy function */
    Int status = SYS_OK ;
    memcpy(attrs->imgOut, attrs->imgIn, attrs->height * attrs->width *2) ;
    return status;
}

int convimg_func (FilterAttrs *attrs)
{
	Uint16 col, row, conv_row, conv_col;
	Int16 x, y;
	Uint32 conv_sum = 0;
    Uint8 *  inImg_ptr  = attrs->imgIn  ;
    Uint8 *  outImg_ptr = attrs->imgOut ;
    Uint16 img_width    = attrs->width  ;
    Uint16 img_height   = attrs->height ;

	// Copy input to output (to get all the chroma pixels right)
	memcpy(outImg_ptr, inImg_ptr, img_height * img_width * 2);

	for (row = KERN_MAX_INDEX; row < (img_height - KERN_MAX_INDEX); row++) {
		for (col = KERN_MAX_INDEX; col < (img_width - KERN_MAX_INDEX); col++) {
			// Now a particular pixel is selected
			if (row < BORDER || row > img_height - BORDER || col < BORDER
					|| col > img_width - BORDER) {
				outImg_ptr[row * 2 * img_width + 2 * col] = 255;
			} else {
				// Perform convolution for this pixel
				for (x = -KERN_MAX_INDEX; x <= KERN_MAX_INDEX; x++) {
					for (y = -KERN_MAX_INDEX; y <= KERN_MAX_INDEX; y++) {
						conv_row = row + x;
						conv_col = col + y;
						conv_sum += inImg_ptr[conv_row * 2 * img_width + 2
								* conv_col];
					}
				}
				// Now this pixel is done, divide and save to output buffer
				outImg_ptr[row * 2 * img_width + 2 * col] = (conv_sum / (KERNEL_SIZE * KERNEL_SIZE));
				conv_sum = 0;
			}
		}
	}
	return SYS_OK;
}

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
    	for ( inner = 0; indexOffsetInner = inner*nextPixelInner < maxInner; inner++ )
    	{
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
    	    offsetImgPtr [ indexOffsetOuter + indexOffsetInner ] = convSum;
    	}
    }
    return SYS_OK;
}
/*
void unsharpenMask( unsigned char* inImg_ptr, unsigned char* outImg_ptr, Uint16 img_width, Uint16 img_height, unsigned char* kernel_ptr )
{
	Uint16 col, row;
	//The two image pointers are switched to make the inpit image blurry.
	convimg( outImg_ptr, inImg_ptr, img_width, img_height, kernel_ptr);
	//Since a border is used in convimg will this affect which pixels this filter will use aswell.
	for (row = KERN_MAX_INDEX; row < (img_height - KERN_MAX_INDEX); row++) {
		for (col = KERN_MAX_INDEX; col < (img_width - KERN_MAX_INDEX); col++) {
			// Now a particular pixel is selected
			if (row > BORDER && row < img_height - BORDER && col > BORDER
					&& col < img_width - BORDER) {
				// Subtract the corresponding pixel in input image from the output image.
				outImg_ptr[row * 2 * img_width + 2 * col] -= inImg_ptr[row * 2 * img_width + 2 * col];
			}
		}
	}

}
*/
