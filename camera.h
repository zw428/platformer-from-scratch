#ifndef CAMERA_H
#define CAMERA_H

#include "SDL2/SDL.h"

class camera
{
public:
	camera();

	void set_camera( SDL_Rect r );
	void set_camera( int x, int y );
	void resize_camera( int w, int h );

	SDL_Point camera_coords( int x, int y );

	bool should_draw( int x, int y, int w, int h );

	SDL_Rect camera_rect();
private:
	SDL_Rect _cam;
};

#endif
