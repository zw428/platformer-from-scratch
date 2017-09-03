#include "image.h"

image::image()
{
	_tex_store.tex = 0;
	_tex_store.orig_w = 0;
	_tex_store.orig_h = 0;
}

void image::draw()
{
	SDL_Rect rect;
	rect.x = x();
	rect.y = y();
	rect.w = w();
	rect.h = h();

	SDL_Renderer* ren = manager::instance()->renderer();

	SDL_RenderCopy(ren, _tex_store.tex, NULL, &rect);
}

void image::texture( texture_store tex_store )
{
	_tex_store = tex_store;
}

texture_store image::tex_store()
{
	return _tex_store;
}
