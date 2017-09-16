#include "anim.h"
#include "manager.h"

anim::anim()
	:image(),
	 _clip_offset(0),
	 _clip_width(0),
	 _frame_dur(5),
	 _frame_counter(0),
	 _index(0)
{
}

void anim::draw()
{
	SDL_Rect rect;

	SDL_Point adjusted_coords = manager::instance()->camera_coords( x(), y() );

	rect.x = adjusted_coords.x;
	rect.y = adjusted_coords.y;
	rect.w = w();
	rect.h = h();

	handle_frame_count();

	SDL_Rect clip;

	clip.x = clip_offset();
	clip.y = 0;
	clip.w = clip_width();
	clip.h = tex_store().orig_h;

	if ( manager::instance()->should_draw( x(), y(), w(), h() ) )
	{
		SDL_RendererFlip f = (flip_h()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(manager::instance()->renderer(), tex_store().tex, &clip, &rect, 0, 0, f );
	}
}

void anim::clip_width( unsigned short width )
{
	_clip_width = width;
}

void anim::clip_offset( unsigned short offset )
{
	_clip_offset = offset;
}

void anim::frame_dur( unsigned short t )
{
	if ( t == 0 )
	{
		t = 1;
	}

	_frame_dur = t;
}

unsigned short anim::clip_offset() const
{
	return _clip_offset;
}

unsigned short anim::clip_width() const
{
	return _clip_width;
}

unsigned short anim::frame_dur() const
{
	return _frame_dur;
}

void anim::handle_frame_count()
{
	if ( _frame_counter < _frame_dur - 1 )
	{
		_frame_counter++;
	}
	else
	{
		_frame_counter = 0;

		if ( ++_index >= tex_store().orig_w / _clip_width )
		{
			_index = 0;
		}
	}

	clip_offset( ( _index )*clip_width() );
}
