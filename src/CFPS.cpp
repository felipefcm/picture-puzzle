
#include "CFPS.h"

CFPS CFPS::fpsControl;

CFPS::CFPS(){
	oldTime = 0;
	lastTime = 0;
	speedFactor = 0;
	numFrames = 0;
	frames = 0;
}

void CFPS::OnLoop(){
	
	if((unsigned) oldTime + 1000 < SDL_GetTicks())
	{
		oldTime = SDL_GetTicks();
		numFrames = frames;
		frames = 0;
	}

	speedFactor = ((SDL_GetTicks() - lastTime) / 1000.0f) * 32.0f;
	lastTime = SDL_GetTicks();
	frames++;
}

int CFPS::getFPS(){
	return numFrames;
}

float CFPS::getSpeedFactor(){
	return speedFactor;
}

