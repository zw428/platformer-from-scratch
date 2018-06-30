#pragma once

#ifndef SHARED_TEXTURE_H
#define SHARED_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class shared_texture
{
public:
	shared_texture();
	shared_texture( SDL_Texture* tex );
	~shared_texture();
	shared_texture( const shared_texture& shr );
	shared_texture operator=( const shared_texture& shr );
	SDL_Texture* tex() const;
	void tex( SDL_Texture* tex );
	unsigned short count() const;
private:
	void create( SDL_Texture* tex );
	void destroy();
	unsigned short* _count;
	SDL_Texture* _tex;
};

#endif
