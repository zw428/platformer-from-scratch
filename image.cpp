#include "image.h"
#include "camera.h"
#include "manager.h"

image::image()
	:_flip_h(0)
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

	if ( manager::instance()->should_draw( x(), y(), w(), h() ) )
	{
		SDL_RendererFlip f = (flip_h()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(manager::instance()->renderer(), _tex_store.tex, 0, &rect, 0, 0, f );
	}
}

void image::texture( texture_store tex_store )
{
	_tex_store = tex_store;
}

texture_store image::tex_store() const
{
	return _tex_store;
}

void image::flip_h( bool flipped )
{
	_flip_h = flipped;
}

bool image::flip_h() const
{
	return _flip_h;
}
