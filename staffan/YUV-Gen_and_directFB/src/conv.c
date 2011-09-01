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




unsigned char* convimg( unsigned char* image_ptr, unsigned char* kernel_ptr)
{
	uint16 col, row, conv_row, conv_col;
	int16 x, y;
	uint8 Y=55;
	uint32 conv_sum = 0;

	printf("KERNEL_SIZE:%u KERN_MAX_INDEX:%u\n", KERNEL_SIZE, KERN_MAX_INDEX);


	// allocate space for output image
	uint8* outImg_ptr = malloc(IMG_HEIGHT*IMG_WIDTH*2*sizeof(uint8));

	// Copy input to output for now (and to get all the chroma pixels right)
	memcpy(outImg_ptr, image_ptr, IMG_HEIGHT*IMG_WIDTH*2);

	for( row=KERN_MAX_INDEX; row<(IMG_HEIGHT-KERN_MAX_INDEX); row++ )
	{
		for( col=KERN_MAX_INDEX; col<(IMG_WIDTH-KERN_MAX_INDEX); col++ )
		{
			// Now a particular pixel is selected
			if( row < BORDER || row > IMG_HEIGHT-BORDER || col < BORDER || col > IMG_WIDTH-BORDER )
			{
				outImg_ptr[row*2*IMG_WIDTH+2*col] = 255;
			}
			else
			{
				// Perform convolution for this pixel
				for( x = -KERN_MAX_INDEX; x <= KERN_MAX_INDEX; x++)
				{
					for( y = -KERN_MAX_INDEX; y <= KERN_MAX_INDEX; y++)
					{
						conv_row = row + x;
						conv_col = col + y;
						conv_sum += image_ptr[ conv_row*2*IMG_WIDTH + 2*conv_col ];
					}
				}
				// Now this pixel is done, divide and save to output buffer
				outImg_ptr[row*2*IMG_WIDTH+2*col] = (conv_sum/(KERNEL_SIZE*KERNEL_SIZE));
				conv_sum = 0;
			}


			// Now a particular pixel is selected
			//outImg_ptr[row*2*IMG_WIDTH+2*col] = Y++;
			//outImg_ptr++;
		}
	}



	free(image_ptr);
	return outImg_ptr;
}


unsigned char* gengrad( uint16 width, uint16 height )
{
	unsigned char *imgptr, *imgptr_cpy;
	uint16 row, col;
	uint8 Y = 0;

	imgptr = malloc( 2*width*height*sizeof(unsigned char) );
	imgptr_cpy = imgptr;

	// loop through rows
	for( row=0; row<height; row++ )
	{
		Y = 0; // reset Y for each row
		// loop through macropixels
		for( col=0; col<width/2; col++ )
		{
			*imgptr_cpy++ = Y++; // Y0
			*imgptr_cpy++ = 50; // Cr
			*imgptr_cpy++ = Y++; // Y1
			*imgptr_cpy++ = 128; // Cb
		}
	}
	return imgptr;
}

unsigned char* genbars( uint16 width, uint16 height )
{
	unsigned char *imgptr, *imgptr_cpy;
	uint16 row, col;
	uint8 Y = 0;

	imgptr = malloc( 2*width*height*sizeof(unsigned char) );
	imgptr_cpy = imgptr;

	// loop through rows
	for( row=0; row<height; row++ )
	{
		//Y = 0; // reset Y for each row
		// loop through macropixels
		for( col=0; col<width/2; col++ )
		{
			if( col % 2 == 0 )
			{
				Y = 0;
			}
			else
			{
				Y = 255;
			}
			*imgptr_cpy++ = Y; // Y0
			*imgptr_cpy++ = 50; // Cr
			*imgptr_cpy++ = Y; // Y1
			*imgptr_cpy++ = 128; // Cb
		}
	}
	return imgptr;
}
