
#include "PicturePuzzle.h"

void PicturePuzzle::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){

	switch(sym)
	{
		case SDLK_s:
			//puzzle.resolver();
		break;

		case SDLK_d:
			puzzle.embaralhar();
		break;
	}
}

void PicturePuzzle::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){

}

void PicturePuzzle::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle){
	puzzle.mouseHover(mX,mY);
}

void PicturePuzzle::OnLButtonDown(int mX, int mY){
	
	//Clique dentro do puzzle?
	if( mX >= puzzle.getPictureX() && mX <= puzzle.getPictureX() + puzzle.getPictureSize())
		if( mY >= puzzle.getPictureY() && mY <= puzzle.getPictureY() + puzzle.getPictureSize())
			if(!puzzle.isHintMode())
				puzzle.LMouseDown(mX,mY);

	//Botões
	if( mX >= puzzle.hintButton.bX && mX <= puzzle.hintButton.bX + puzzle.hintButton.getWidth() )
		if( mY >= puzzle.hintButton.bY && mY <= puzzle.hintButton.bY + puzzle.hintButton.getHeight() )
			puzzle.hintButton.action(&puzzle);
		
}

void PicturePuzzle::OnLButtonUp(int mX, int mY){

}