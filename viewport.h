#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SDL2/SDL.h>

class viewport
{
public:
	viewport();

	SDL_Rect get_viewport();
	void set_viewport( int x, int y, int w, int h );
private:
	SDL_Rect _rect;
};

#endif
