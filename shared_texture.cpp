#include "shared_texture.h"

shared_texture::shared_texture()
	:_count(0)
{
	create(0);
}

shared_texture::shared_texture( SDL_Texture* tex )
{
	create(tex);
}

shared_texture::~shared_texture()
{
	destroy();
}

shared_texture::shared_texture(const shared_texture& shr)
{
	_count = shr._count;
	(*_count)++;
	_tex = shr._tex;
}

shared_texture shared_texture::operator=( const shared_texture& shr )
{
	_count = shr._count;
	(*_count)++;
	_tex = shr._tex;

	return *this;
}

void shared_texture::tex( SDL_Texture* tex )
{
	if ( tex == _tex )
	{
		return;
	}

	create(tex);
}

SDL_Texture* shared_texture::tex() const
{
	return _tex;
}

unsigned short shared_texture::count() const
{
	if ( _count )
	{
		return *_count;
	}

	return 0;
}

void shared_texture::create( SDL_Texture* tex )
{
	_tex = tex;

	if ( !_count )
	{
		_count = new unsigned short(1);
	}
}

void shared_texture::destroy()
{
	if ( *_count == 1 )
	{
		SDL_DestroyTexture(_tex);
		_tex = 0;
		delete _count;
		_count = 0;
	}
	else
	{
		(*_count)--;
	}
}
