
#ifndef _TEXTO_H
#define _TEXTO_H

#include <SDL\SDL_ttf.h>
#include <vector>

#include "CSurface.h"
#include "defs.h"

class Texto {

	protected:
		SDL_Surface* fontSurface;

	private:
		char *texto;
		bool visivel;
		bool blended;
		TTF_Font* font;
		SDL_Color	fgColor;
		SDL_Color	bgColor;

		void refreshSurface();

	public:
		Texto();
		static std::vector<Texto*> textList;

		float x;
		float y;
		void setText(char *str);
		void setVisivel(bool);
		void setBlended(bool);
		void setFgColor(Uint8 r, Uint8 g, Uint8 b);
		void setBgColor(Uint8 r, Uint8 g, Uint8 b);
		void center();
		void center(int left,int right);
		int getWidth();
		int getHeight();
		bool onLoad(char* fontFile, int size);
		SDL_Surface* getTextSurface();
		virtual void onRender(SDL_Surface* destSurface);
		void onCleanup();
};

#endif