
#ifndef _CFPS_H
#define _CFPS_H

#include <SDL\SDL.h>

class CFPS {

	private:
		int oldTime;
		int lastTime;
		float speedFactor;
		int numFrames;
		int frames;

	public:
		static CFPS fpsControl;

		CFPS();
		void OnLoop();
		int getFPS();
		float getSpeedFactor();
};

#endif