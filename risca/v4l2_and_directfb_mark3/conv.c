#include "conv.h"
// TODO: include the h-file where ImageAttrs is defined.
void convBox1D ( ImageAttrs convAttrs )
{
    unsigned int outer = 0, inner = 0, nextPixelOuter, nextPixelInner, maxOuter, indexOffsetOuter, indexOffsetInner, maxInner, convSum kernelSideWidth;

    char *offsetImgPtr = convAttrs.img + convAttrs.offset;
    kernelSideWidth = (convAttrs.kernel - 1)/2;

    // convAttrs.orientation = 1 represents vertical and = 0 horizontal.
    if ( convAttrs.orientation )
    {
        nextPixelOuter = convAttrs.spacing;
    	nextPixelInner = convAttrs.width*MACROPIXEL_SIZE;
    	maxOuter = nextPixelInner;
    	maxInner = convAttrs.height;
    }
    else
    {
        nextPixelOuter = convAttrs.width*MACROPIXEL_SIZE;
        nextPixelInner = convAttrs.spacing;
        maxOuter = convAttrs.height;
    	maxInner = nextPixelOuter;
    }
    for ( outer; indexOffsetOuter = outer*nextPixelOuter < maxOuter; outer++ )
    {
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
    	        convSum += offsetImgPtr[ indexOffsetOuter + nextPixelInner*( inner + kernelSideWidth ];
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
    	        convSum -= offsetImgPtr[ indexOffsetOuter nextPixelInner*( inner - kernelSideWidth - 1) ];
    	    }
    	    // Store the value.
    	    offsetImgPtr [ indexOffsetOuter + indexOffsetInner ];
    	}
    }

}
