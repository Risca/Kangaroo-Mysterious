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

void convimg(unsigned char* inImg_ptr, unsigned char* outImg_ptr, uint16 img_width, uint16 img_height, unsigned char* kernel_ptr)
{
	uint16 col, row, conv_row, conv_col;
	int16 x, y;
	uint32 conv_sum = 0;
	(void)kernel_ptr;

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

	free(inImg_ptr);
	return;
}

