#include "anim.h"
#include "manager.h"

anim::anim()
	:image(),
	 _clip_offset(0),
	 _clip_width(0),
	 _frame_counter(0),
	 _index(0)
{
}

void anim::draw()
{
	SDL_Rect rect;

	SDL_Point adjusted_coords = manager::instance()->cam.camera_coords( x(), y() );

	rect.x = adjusted_coords.x;
	rect.y = adjusted_coords.y;
	rect.w = w();
	rect.h = h();

	handle_frame_count();

	if ( !manager::instance()->cam.should_draw( x(), y(), w(), h() ) )
	{
		return;
	}

	SDL_RendererFlip f = (flip_h()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if ( num_frames() > 1 )
	{
		SDL_Rect clip;
		clip.x = clip_offset();
		clip.y = 0;
		clip.w = clip_width();
		clip.h = tex_store().orig_h;
		SDL_RenderCopyEx(manager::instance()->renderer(), tex_store().tex, &clip, &rect, 0, 0, f );
	}
	else
	{
		SDL_RenderCopyEx(manager::instance()->renderer(), tex_store().tex, 0, &rect, 0, 0, f );
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

void anim::add_frame_dur( unsigned short t )
{
	unsigned short frame_dur = t;

	if ( t == 0 )
	{
		frame_dur = 1;
	}

	_frame_durs.push_back(frame_dur);
}

unsigned short anim::clip_offset() const
{
	return _clip_offset;
}

unsigned short anim::clip_width() const
{
	return _clip_width;
}

unsigned short anim::num_frames() const
{
	if ( clip_width() == 0 )
	{
		return 1;
	}

	return tex_store().orig_w / clip_width();
}

bool anim::at_end() const
{
	return ( _frame_counter == _frame_durs[_index] - 2 && _index == num_frames() - 1);
}

void anim::reset()
{
	_index = 0;
}

void anim::handle_frame_count()
{
	if ( num_frames() == 1 )
	{
		return;
	}

	if ( _frame_durs.size() != num_frames() )
	{
		throw( "not enough frames for animation" );
	}

	if ( _frame_counter < _frame_durs[_index] - 1 )
	{
		_frame_counter++;
	}
	else
	{
		_frame_counter = 0;

		if ( ++_index >= num_frames() )
		{
			_index = 0;
		}
	}

	clip_offset( ( _index )*clip_width() );
}
