
#include "Chronometer.h"

Chronometer::Chronometer(){
	zera();
}

void Chronometer::zera(){
	running = false;
	h = 0;
	m = 0;
	s = 0;
}

bool Chronometer::init(){
	
	if(!Texto::onLoad("fonts/Polo Brush.ttf", 26))
		return false;

	Texto::setText("0:00");

	return true;
}

void Chronometer::start(){
	running = true;
	oldTime = SDL_GetTicks();
}

void Chronometer::stop(){
	running = false;
}

void Chronometer::setTime(int h, int m, int s){

	if(h >= 0 && h < 60)
		if(m >= 0 && m < 60)
			if(s >= 0 && s < 60)
			{
				this->h = h;
				this->m = m;
				this->s = s;
			}
}

void Chronometer::addSegundo(){
	if(s < 59)
		s++;
	else
	{
		addMinuto();
		s = 0;
	}
}

void Chronometer::addMinuto(){
	if(m < 59)
		m++;
	else
	{
		addHora();
		m = 0;
	}
}

void Chronometer::addHora(){
	h++;
}

void Chronometer::loop(){
	
	if(!running)
		return;
	
	if(SDL_GetTicks() >= oldTime + 1000)
	{
		addSegundo();
		oldTime = SDL_GetTicks();
	}

	char str[7];
	sprintf_s(str,"%d:%.2d", h, m);
	Texto::setText(str);
}

void Chronometer::render(SDL_Surface *destSurface){
	Texto::onRender(destSurface);
}

void Chronometer::cleanup(){
	Texto::onCleanup();
}