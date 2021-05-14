
#include "PicturePuzzle.h"

bool PicturePuzzle::init(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	if(TTF_Init() < 0)
		return false;

	displaySurface = SDL_SetVideoMode(WND_WIDTH, WND_HEIGHT, COLOR_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(!displaySurface)
		return false;

	//Puzzle
	puzzle.setPictureSize(500);

	if(!puzzle.load("images/mp.jpg"))
		return false;

	puzzle.setDimensao(8);

	if(!puzzle.init())
		return false;

	puzzle.embaralhar();

	return true;
}