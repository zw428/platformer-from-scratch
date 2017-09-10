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

	void draw();
	void texture( texture_store tex_store );
	texture_store tex_store() const;

	void flip_h( bool flipped );
	bool flip_h() const;
private:
	texture_store _tex_store;

	bool _flip_h;
};

#endif
