
#include "PicturePuzzle.h"

void PicturePuzzle::loop(){

	puzzle.loop();
	
	CFPS::fpsControl.OnLoop();

#ifdef _DEBUG
	sprintf_s(windowTitle, "FPS: %d | (%d,%d) - %d", CFPS::fpsControl.getFPS(),puzzle.getSelected().linha, puzzle.getSelected().coluna, puzzle.getPeca(puzzle.getSelected()));
	SDL_WM_SetCaption(windowTitle,NULL);
#else
	SDL_WM_SetCaption("PicturePuzzle",NULL);
#endif

	SDL_Delay(1);
}