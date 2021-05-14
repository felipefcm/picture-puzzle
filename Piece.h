
#ifndef _PIECE_H
#define _PIECE_H

#include <SDL\SDL.h>

#include "CSurface.h"

class Piece {

	private:
		SDL_Surface* pieceSurface;

	public:
		Piece();

		float x;
		float y;
		
		bool load(SDL_Surface* pictureSurface, int x, int y, int w, int h);
		void render(SDL_Surface* destSurface);
		void cleanup();
};

#endif