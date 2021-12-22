
#include "Piece.h"

Piece::Piece(){
	pieceSurface = NULL;
	x = 0;
	y = 0;
}

bool Piece::load(SDL_Surface* pictureSurface, int x, int y, int w, int h){

	if(!pictureSurface)
		return false;

	SDL_Rect srcRect;
	srcRect.x = x;
	srcRect.y = y;
	srcRect.w = w;
	srcRect.h = h;

	if(!pieceSurface)
		pieceSurface = SDL_CreateRGBSurface(pictureSurface->flags, w, h, 16, 0,0,0, SDL_ALPHA_OPAQUE);

	SDL_BlitSurface(pictureSurface, &srcRect, pieceSurface, NULL);

	if(!pieceSurface)
		return false;
	
	return true;
}

void Piece::render(SDL_Surface* destSurface){
	if(destSurface && pieceSurface)
		CSurface::OnDraw(destSurface, pieceSurface, (int)x, (int)y);
}

void Piece::cleanup(){
	if(pieceSurface)
		SDL_FreeSurface(pieceSurface);
}

