//============================================================================
// Name        : SDL-test3.cpp
// Author      : Staffan Sjöqvist
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// Lib includes
#include "SDL.h"
#include "SDL_events.h"

// Own includes
#include "SDL_inc.h"
#include "defines.h"

SDL_Surface *  surface = NULL;
SDL_Overlay *  image   = NULL;
unsigned short pitch   = WIDTH*2;
SDL_Rect rect = {0,0,WIDTH,HEIGHT};

void initSDL ()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Init error!");
	}
    atexit(SDL_Quit);

	// Create video surface
	surface = SDL_SetVideoMode (WIDTH, HEIGHT, 24, SDL_HWSURFACE || SDL_DOUBLEBUF);
    if (surface) {
        printf("SDL_Surface created successfully\n");
    }

    /* Create overlay */
	image = SDL_CreateYUVOverlay (WIDTH, HEIGHT, SDL_YUY2_OVERLAY, surface);
    if (image)
        printf("SDL_Overlay created successfully\n");

	image->pitches = &pitch;
	image->planes = 1;
}

void displayFrame (unsigned char * f)
{
 	image->pixels = &f;
	SDL_DisplayYUVOverlay(image, &rect);
}
