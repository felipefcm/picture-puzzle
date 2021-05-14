
#include "Botao.h"
#include "Puzzle.h"

Botao::Botao(){
	
	visible = true;
	
	x = 0;
	y = 0;
	
	bgSurface = NULL;
}

bool Botao::init(char* bgImageFile, int posX, int posY){
	
	if(!Texto::onLoad("fonts/Polo Brush.ttf",26))
		return false;

	if(posX < 0 || posY < 0)
		return false;

	bX = posX;
	bY = posY;

	if(bgImageFile != NULL)
	{
		if((bgSurface = CSurface::OnLoad(bgImageFile)) == NULL)
			return false;

		x = (float) bX;
		y = (float) bY;
	}
	else
	{
		x = (float) bX;
		y = (float) bY;
	}

	return true;
}

void Botao::render(SDL_Surface* destSurface){
	
	if(bgSurface)
		CSurface::OnDraw(destSurface, bgSurface, bX, bY);
		
	Texto::onRender(destSurface);
}

void Botao::action(Puzzle* pPuzzle){
	//Virtual function
}

void Botao::cleanup(){
	
	if(bgSurface)
		SDL_FreeSurface(bgSurface);

	Texto::onCleanup();
}

int Botao::getWidth(){
	return bgSurface->w;
}

int Botao::getHeight(){
	return bgSurface->h;
}

void Botao::centerX(int left, int right){
	bX = (left + right) / 2 - bgSurface->w / 2;
}

