#include "viewport.h"

viewport::viewport()
{
}

SDL_Rect viewport::get_viewport()
{
	return _rect;
}

void viewport::set_viewport( int x, int y, int w, int h )
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}

