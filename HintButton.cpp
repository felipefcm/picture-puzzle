
#include "HintButton.h"
#include "Puzzle.h"

HintButton::HintButton(){
	pressed = false;
}

void HintButton::setText(char *str){
	
	Botao::setText(str);

	x = (float) bX + bgSurface->w / 2 - Texto::fontSurface->w / 2;
	y = (float) bY + bgSurface->h / 2 - Texto::fontSurface->h / 2;
}

bool HintButton::init(char* bgFileName, int posX, int posY){
	
	if(!Botao::init(bgFileName,posX,posY))
		return false;

	return true;
}

void HintButton::render(SDL_Surface* destSurface){
	Botao::render(destSurface);
}

void HintButton::action(Puzzle* pPuzzle){
	
	if(!pressed)
	{
		setText("Back");
		pressed = true;
		pPuzzle->setHintMode(true);
	}
	else
	{
		setText("Hint");
		pressed = false;
		pPuzzle->setHintMode(false);
	}

}

void HintButton::cleanup(){
	Botao::cleanup();
}

