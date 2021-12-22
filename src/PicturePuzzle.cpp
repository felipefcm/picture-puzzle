
#include "PicturePuzzle.h"

PicturePuzzle::PicturePuzzle(){
	running = false;
	displaySurface = NULL;
}

int PicturePuzzle::execute(){
	
	srand((unsigned int) time(NULL));

	if(!init())
		return -1;

	SDL_Event e;

	running = true;

	while(running)
	{
		while(SDL_PollEvent(&e))
			CEvent::OnEvent(&e);

		loop();
		render();
	}

	cleanup();

	return 0;
}

void PicturePuzzle::OnExit(){
	running = false;
}