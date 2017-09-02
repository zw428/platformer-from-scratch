#include "anim.h"

anim::anim()
	:image(),
	 _clip_offset(0),
	 _frame_counter(0)
{
}

void anim::draw()
{
	SDL_Rect rect;
	rect.x = x();
	rect.y = y();
	rect.w = w();
	rect.h = h();

	handle_frame_count();

	SDL_Rect clip;

	clip.x = clip_offset();
	clip.y = 0;
	clip.w = clip_width();
	clip.h = tex_store().orig_h;

	SDL_RenderCopy(manager::instance()->renderer(), tex_store().tex, &clip, &rect);
}

void anim::clip_width( unsigned short width )
{
	_clip_width = width;
}

void anim::clip_offset( unsigned short offset )
{
	_clip_offset = offset;
}

unsigned short anim::clip_offset()
{
	return _clip_offset;
}

unsigned short anim::clip_width()
{
	return _clip_width;
}

void anim::frame_dur( unsigned short t )
{
	_frame_dur = t;
}

unsigned short anim::frame_dur()
{
	return _frame_dur;
}

void anim::handle_frame_count()
{
	static unsigned short index = 0;

	clip_offset( ( index )*clip_width() );

	if ( _frame_counter < _frame_dur )
	{
		_frame_counter++;
	}
	else
	{
		_frame_counter = 0;

		if ( ++index >= tex_store().orig_w / _clip_width )
		{
			index = 0;
		}
	}
}
