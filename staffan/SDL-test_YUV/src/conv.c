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
//#include <filters.h>
/*  ----------------------------------- DSP/BIOS Headers            */
//#include <sys.h>

int bypass_func (FilterAttrs *attrs)
{
    /* I am a dummy function */
    int status = SYS_OK ;
    memcpy(attrs->imgOut, attrs->imgIn, attrs->height * attrs->width *2) ;
    return status;
}

int convimg_func (FilterAttrs *attrs)
{
	Uint16 col, row, conv_row, conv_col;
	Int16 x, y;
	Uint32 conv_sum = 0;
    Uint8 * inImg_ptr      = attrs->imgIn            ;
    Uint8 * outImg_ptr     = attrs->imgOut           ;
    Uint16  img_width      = attrs->width            ;
    Uint16  img_height     = attrs->height           ;
    Uint8   kern_max_index = (attrs->kernelSize-1)/2 ;

	// Copy input to output (to get all the chroma pixels right)
	memcpy(outImg_ptr, inImg_ptr, img_height * img_width * 2);

	for (row = kern_max_index; row < (img_height - kern_max_index); row++) {
		for (col = kern_max_index; col < (img_width - kern_max_index); col++) {
			// Now a particular pixel is selected
			if (row < BORDER || row > img_height - BORDER || col < BORDER
					|| col > img_width - BORDER) {
				outImg_ptr[row * 2 * img_width + 2 * col] = 255;
			} else {
				// Perform convolution for this pixel
				for (x = -kern_max_index; x <= kern_max_index; x++) {
					for (y = -kern_max_index; y <= kern_max_index; y++) {
						conv_row = row + x;
						conv_col = col + y;
						conv_sum += inImg_ptr[conv_row * 2 * img_width + 2
								* conv_col];
					}
				}
				// Now this pixel is done, divide and save to output buffer
				outImg_ptr[row * 2 * img_width + 2 * col] = (conv_sum / (attrs->kernelSize * attrs->kernelSize));
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
    	nextPixelInner = attrs->width * BYTES_PER_PIXEL;
    	maxOuter = attrs->width * BYTES_PER_PIXEL / attrs->spacing;
    	maxInner = attrs->height;
    }
    else
    {
        nextPixelOuter = attrs->width * BYTES_PER_PIXEL;
        nextPixelInner = attrs->spacing;
        maxOuter = attrs->height;
    	maxInner = attrs->width * BYTES_PER_PIXEL / attrs->spacing;
    }
    for ( outer=0; outer < maxOuter; outer++ )
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
    	for ( inner = 0; inner < maxInner; inner++ )
    	{
            indexOffsetInner = inner*nextPixelInner;
    	    // Check if the last pixel used in the convolution is outside the range.
    	    if ( ( inner + kernelSideWidth ) < maxInner )
    	    {
    	        convSum += offsetImgPtr[ indexOffsetOuter + nextPixelInner*( inner + kernelSideWidth ) ];
    	    }
    	    else
    	    {
    	        // Add the max border value.
    	    	convSum += offsetImgPtr[ indexOffsetOuter + (maxInner - 1)*attrs->spacing ];
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
/*
void unsharpenMask( unsigned char* inImg_ptr, unsigned char* outImg_ptr, Uint16 img_width, Uint16 img_height, unsigned char* kernel_ptr )
{
	Uint16 col, row;
	//The two image pointers are switched to make the inpit image blurry.
	convimg( outImg_ptr, inImg_ptr, img_width, img_height, kernel_ptr);
	//Since a border is used in convimg will this affect which pixels this filter will use aswell.
	for (row = kern_max_index; row < (img_height - kern_max_index); row++) {
		for (col = kern_max_index; col < (img_width - kern_max_index); col++) {
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

/*
 * BW-filter, sets all chreoma pixels to 128, copies all luma pixels.
 */
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
