#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "shared_texture.h"

class text
{
public:
	text();
	bool set_text( const char* str );
	void draw( unsigned short x, unsigned short y, unsigned short h );
private:
	unsigned short _orig_width;
	unsigned short _orig_height;
	shared_texture _shr_tex;
};

#endif
