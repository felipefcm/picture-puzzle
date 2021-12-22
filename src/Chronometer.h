
#ifndef _CHRONOMETER_H
#define _CHRONOMETER_H

#include "Texto.h"

class Chronometer : public Texto {
	
	private:
		int h, m, s;
		bool running;

		void addSegundo();
		void addMinuto();
		void addHora();

		unsigned int oldTime;
		
	public:
		Chronometer();

		void zera();
		void start();
		void stop();
		void setTime(int h, int m, int s);

		bool init();
		void loop();
		void render(SDL_Surface*);
		void cleanup();
};

#endif