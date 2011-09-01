//============================================================================
// Name        : SDL-test3.cpp
// Author      : Staffan Sjöqvist
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// Lib includes
#include <iostream>
#include "SDL.h"
#include "SDL_events.h"
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>


// Own includes
#include "conv.h"


using namespace std;

int main(int argc, char* argv[]) {
	// Check for correct number of input arguments
	if (argc != 2) {
		cerr << "Must have one filename as input parameter" << endl;
		exit(1);
	}

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Init error!" << endl;
	}
	atexit(SDL_Quit);

	// Open file
	fstream infile;
	infile.open(argv[1]);

	int height = 480;
	int width = 640;

	// Find input file size
	struct stat results;
	stat(argv[1], &results);
	int filesize = results.st_size;
	cout << "File size: " << filesize << " bytes" << endl;

	// Allocate space for infile
	Uint8* pxData;
	pxData = new Uint8[filesize];
	infile.read((char*)pxData, filesize);


	cout << "Width: " << width << " Height: " << height << endl;

	// Create video surface
	SDL_Surface* surface = SDL_SetVideoMode(width, height, 24, 0);


	SDL_Overlay* image = SDL_CreateYUVOverlay(640, 480, SDL_YUY2_OVERLAY, surface );
	image->planes = 1;
	Uint16 pitch = 1280;
	image->pitches = &pitch;
	//image->pixels = &pxData;
	unsigned char *imgptr = genimg(640, 480);
	//cout << (unsigned long int)imgptr << endl;
	image->pixels = &imgptr;

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 640;
	rect.h = 480;


	SDL_DisplayYUVOverlay(image, &rect);



	//Wait for Escape key
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
		if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
			break;

		// Wrong event, wait more
	}
	cout << "Exiting";

	delete imgptr;
	delete pxData;
	exit(0);

	return 0;
}
