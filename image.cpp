#include "image.h"
#include "camera.h"

image::image()
{
	_tex_store.tex = 0;
	_tex_store.orig_w = 0;
	_tex_store.orig_h = 0;
}

void image::draw()
{
	SDL_Rect rect;

	SDL_Point adjusted_coords = manager::instance()->camera_coords( x(), y() );

	rect.x = adjusted_coords.x;
	rect.y = adjusted_coords.y;
	rect.w = w();
	rect.h = h();

	SDL_Renderer* ren = manager::instance()->renderer();

	if ( manager::instance()->should_draw( x(), y(), w(), h() ) )
	{
		SDL_RenderCopy(ren, _tex_store.tex, NULL, &rect);
	}
}

void image::texture( texture_store tex_store )
{
	_tex_store = tex_store;
}

texture_store image::tex_store()
{
	return _tex_store;
}
