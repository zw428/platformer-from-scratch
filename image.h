#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "manager.h"
#include "box.h"

class image : public box
{
public:
	image();

	virtual void draw();
	void texture( texture_store tex_store );
	texture_store tex_store();

	static void set_renderer( SDL_Renderer* renderer );
private:
	texture_store _tex_store;

	unsigned short _x;
	unsigned short _y;
	unsigned short _w;
	unsigned short _h;

	static SDL_Renderer* _ren;
};

#endif
