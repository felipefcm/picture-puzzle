
#include "PicturePuzzle.h"

void PicturePuzzle::cleanup(){

	if(displaySurface)
		SDL_FreeSurface(displaySurface);

	displaySurface = NULL;

	puzzle.cleanup();
	
	TTF_Quit();
	SDL_Quit();
}