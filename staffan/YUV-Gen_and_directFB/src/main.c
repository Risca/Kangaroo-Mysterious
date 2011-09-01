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
#include <string.h>
#include "conv.h"
#include "directfb_inc.h"

int main(int argc, char* argv[])
{
	uint8* (*render_fcn)(uint16, uint16);
	if( argc > 1 )
	{
		if( !strcmp(argv[1], "-bars") )
		{
			render_fcn = genbars;
		}
		else if( !strcmp(argv[1], "-grad") )
		{
			render_fcn = gengrad;
		}
		else
		{
			printf("Give me some arguments, asshole!");
			render_fcn = NULL;
		}

	}
	// init directFB
	directfb_init(0, NULL);

	// Generate an image
	uint8 *image = render_fcn(640, 480);
	image = convimg(image, NULL);


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
