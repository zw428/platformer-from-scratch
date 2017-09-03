#include "camera.h"

camera::camera()
{
	_cam.x = 0;
	_cam.y = 0;
	_cam.w = 0;
	_cam.h = 0;
}

void camera::set_camera( SDL_Rect r )
{
	_cam = r;
}
void camera::set_camera( int x, int y )
{
	_cam.x = x;
	_cam.y = y;
}

void camera::resize_camera( int w, int h )
{
	_cam.w = w;
	_cam.h = h;
}

SDL_Point camera::camera_coords( int x, int y )
{
	SDL_Point p;

	p.x = x - _cam.x;
	p.y = y - _cam.y;

	return p;
}

bool camera::should_draw( int x, int y, int w, int h )
{
	if ( x + w < _cam.x ||
	     x > _cam.x + _cam.w ||
	     y + h < _cam.y ||
	     y > _cam.y + _cam.h )
	{
		return false;
	}

	return true;
}

SDL_Rect camera::camera_rect()
{
	return _cam;
}
