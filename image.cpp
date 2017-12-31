#include "image.h"
#include "camera.h"
#include "manager.h"

image::image()
	:_flip_h(false),
	 _tiled(false)
{
	_tex_store.tex = 0;
	_tex_store.orig_w = 0;
	_tex_store.orig_h = 0;
}

void image::draw()
{
	if ( !manager::instance()->cam.should_draw( x(), y(), w(), h() ) )
	{
		return;
	}

	if ( tiled() )
	{
		draw_tiled();
	}
	else
	{
		draw_stretched();
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

bool image::tiled() const
{
	return _tiled;
}

void image::tiled( bool tiled )
{
	_tiled = tiled;
}

void image::draw_stretched()
{
	SDL_Point adjusted_coords = manager::instance()->cam.camera_coords( x(), y() );
	SDL_RendererFlip f = (flip_h()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Rect rect;
	rect.x = adjusted_coords.x;
	rect.y = adjusted_coords.y;
	rect.w = w();
	rect.h = h();

	SDL_RenderCopyEx(manager::instance()->renderer(), _tex_store.tex, 0, &rect, 0, 0, f );
}

void image::draw_tiled()
{
	SDL_Point adjusted_coords = manager::instance()->cam.camera_coords( x(), y() );

	SDL_Rect rect;
	rect.x = adjusted_coords.x;
	rect.y = adjusted_coords.y;
	rect.w = _tex_store.orig_w;
	rect.h = _tex_store.orig_h;

	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = rect.w;
	clip.h = rect.h;

	for ( unsigned i=0; i < std::ceil( float(h())/_tex_store.orig_h ); i++ )
	{
		int height_diff = rect.y + rect.h - adjusted_coords.y - h();

		if ( height_diff > 0 )
		{
			clip.h = rect.h - height_diff;
			rect.h = clip.h;
		}

		for ( unsigned j=0; j < std::ceil( float(w())/_tex_store.orig_w ); j++ )
		{
			int width_diff = rect.x + rect.w - adjusted_coords.x - w();

			if ( width_diff > 0 )
			{
				clip.w = rect.w - width_diff;
				rect.w = clip.w;
				SDL_RenderCopy(manager::instance()->renderer(), _tex_store.tex, &clip, &rect );
				rect.w = _tex_store.orig_w;
			}
			else
			{
				SDL_RenderCopy(manager::instance()->renderer(), _tex_store.tex, 0, &rect );
			}

			rect.x += rect.w;
		}

		rect.y += rect.h;
		rect.h = _tex_store.orig_h;
		rect.x = adjusted_coords.x;
	}
}
