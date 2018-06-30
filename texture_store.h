#pragma once

#ifndef TEXTURE_STORE_H
#define TEXTURE_STORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct texture_store {
	SDL_Texture* tex;
	unsigned short orig_w;
	unsigned short orig_h;
};

#endif
