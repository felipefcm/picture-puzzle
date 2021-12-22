
#ifndef _CBOTAO_H
#define _CBOTAO_H

#include "Texto.h"

class Puzzle;

class Botao : public Texto {

	protected:
		bool visible;
		SDL_Surface* bgSurface;

	public:
		Botao();

		int bX, bY;

		bool init(char* bgImageFile, int posX, int posY);
		void render(SDL_Surface*);
		virtual void action(Puzzle* pPuzzle);
		void cleanup();

		void setVisible(bool);
		int getWidth();
		int getHeight();
		void centerX(int left, int right);
};

#endif