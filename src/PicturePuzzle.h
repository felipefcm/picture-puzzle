
#ifndef _PICTUREPUZZLE_H
#define _PICTUREPUZZLE_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SDL\SDL.h>

#include "CSurface.h"
#include "Texto.h"
#include "CFPS.h"
#include "CEvent.h"
#include "Puzzle.h"

class PicturePuzzle : public CEvent {

	private:
		bool running;
		SDL_Surface* displaySurface;
		char windowTitle[50];
		Puzzle puzzle;

	public:
		PicturePuzzle();

		bool init();
		int execute();
		void loop();
		void render();
		void cleanup();

		//From CEvent
		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnLButtonDown(int mX, int mY);
		void OnLButtonUp(int mX, int mY);
		void OnExit();
};

#endif