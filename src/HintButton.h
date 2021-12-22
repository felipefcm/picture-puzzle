
#ifndef _HINTBUTTON_H
#define _HINTBUTTON_H

#include "Botao.h"

class HintButton : public Botao {

	private:
		bool pressed;

	public:
		HintButton();

		bool init(char* bgFileName, int posX, int posY);
		void setText(char*);
		void render(SDL_Surface*);
		void action(Puzzle* pPuzzle);
		void cleanup();
};

#endif