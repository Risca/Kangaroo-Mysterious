/*
 ============================================================================
 Name        : YUV-Gen_and_directFB.c
 Author      : Staffan Söqvist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "conv.h"
#include "directfb_inc.h"

int main(void)
{
	// init directFB
	directfb_init(0, NULL);

	// Generate an image
	uint8 *image = genimg(640, 480);

	// display image
	directfb_render(image);

	printf("Press ENTER to exit");
	char c = getchar();
	while( c != '\n' )
		c = getchar();

	directfb_release();
	free(image);

	puts("!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
