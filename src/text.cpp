#include "text.h"
#include "manager.h"

text::text()
{
}

bool text::set_text( const char* str )
{
	SDL_Color color = { 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Solid( manager::instance()->resources.fonts("test"), str, color );

	if ( !surface )
	{
		printf( "text load fail '%s'\n", str );
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface( manager::instance()->renderer(), surface );

	if ( !tex )
	{
		printf( "couldn't create texture from text '%s'; sdl error: %s\n", str, SDL_GetError() );
		return false;
	}

	_orig_width = surface->w;
	_orig_height = surface->h;

	SDL_FreeSurface( surface );

	_shr_tex.tex(tex);

	return true;
}

void text::draw( unsigned short x, unsigned short y, unsigned short h )
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = std::round( (float(h)/_orig_height)*_orig_width );

	SDL_RenderCopy(manager::instance()->renderer(), _shr_tex.tex(), NULL, &rect);
}
