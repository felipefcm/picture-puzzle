
#ifndef _PUZZLE_H
#define _PUZZLE_H

#include <math.h>

#include "SDL_rotozoom.h"
#include "CSurface.h"
#include "Texto.h"
#include "defs.h"
#include "Chronometer.h"
#include "HintButton.h"

struct PecaPos {
	int linha;
	int coluna;
};

class Puzzle {

	private:
		int** grid;
		int** solvedGrid;
		int dimensao;
		int pictureX;
		int pictureY;
		int pictureSize;
		int pieceSize;
		PecaPos pSelected;
		bool hasSelected;
		SDL_Rect pictureRect;
		SDL_Rect pieceSelectedRect;
		bool isMouseHovering;
		int hoverX, hoverY;
		SDL_Surface* hoverPieceSurface;
		int moves;
		bool hintMode;

		Chronometer time;

		Texto gameTitleText;
		Texto movesText;
		Texto movesQtText;
		Texto timeText;
		Texto correctText;
		Texto correctQtText;

		//Resized picture
		SDL_Surface* picture;

		int** alocaGrid();
		void deletaGrid(int**);
		void drawPiece(SDL_Surface*, int, int, int);

	public:
		Puzzle();

		HintButton hintButton;

		bool init();
		bool initTexts();
		bool load(char *file);
		void loop();
		void render(SDL_Surface* destSurface);
		void cleanup();

		bool setDimensao(int d);
		void setPictureSize(int size);
		PecaPos getSolutionPecaPos(int p);
		int getPeca(PecaPos pos);
		PecaPos getSelected();

		int getPictureX();
		int getPictureY();
		void setPictureX(int x);
		void setPictureY(int y);
		int getPictureSize();
		void centerX();
		void centerY();
		void centerXY();

		int checkCorretas();
		void swapElements(PecaPos pos1, PecaPos pos2);
		void embaralhar();
		void resolver(int**);
		void switchGrid(int**);
		void setHintMode(bool);
		bool isHintMode(){return hintMode;}

		void LMouseDown(int mx, int my);
		void mouseHover(int posx, int posy);
};

#endif