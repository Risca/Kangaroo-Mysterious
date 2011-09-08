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
