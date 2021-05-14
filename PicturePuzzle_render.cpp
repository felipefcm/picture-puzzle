
#include "PicturePuzzle.h"

void PicturePuzzle::render(){

	SDL_FillRect(displaySurface, NULL, SDL_MapRGB(displaySurface->format, 59, 89, 152));

	puzzle.render(displaySurface);

	SDL_Flip(displaySurface);
}