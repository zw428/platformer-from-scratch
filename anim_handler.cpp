#include "anim_handler.h"

anim_handler::anim_handler()
	:_current_anim(0),
	 _override_anim_active(false),
	 _flipped(false)
{
	the_origin.set_dir(origin_bottom);
}

void anim_handler::think( bool on_ground, bool facing_left, bool moving, bool hanging, bool disabled )
{
	_flipped = facing_left;

	if ( _override_anim_active && _current_anim && !_current_anim->at_end() )
	{
		return;
	}
	else
	{
		_override_anim_active = false;
	}

	if ( hanging )
	{
		_current_anim = &_hanging_anim;
		return;
	}

	if ( disabled )
	{
		_current_anim = &_disabled_anim;
		return;
	}

	if ( on_ground && !moving )
	{
		_current_anim = &_idle_anim;
		return;
	}

	if ( on_ground && moving )
	{
		_current_anim = &_running_anim;
		return;
	}

	if ( !on_ground )
	{
		_current_anim = &_jumping_anim;
		return;
	}

	_current_anim = &_idle_anim;
}

void anim_handler::draw( const box& ref )
{
	if ( !_current_anim )
	{
		return;
	}

	_current_anim->x( ref.x() );
	_current_anim->y( ref.y() );
	_current_anim->flip_h( _flipped );

	the_origin.apply( *_current_anim, ref );

	_current_anim->draw();
}

void anim_handler::set_running_anim( anim a )
{
	_running_anim = a;
}

void anim_handler::set_idle_anim( anim a )
{
	_idle_anim = a;
}

void anim_handler::set_jumping_anim( anim a )
{
	_jumping_anim = a;
}

void anim_handler::set_disabled_anim( anim a )
{
	_disabled_anim = a;
}

void anim_handler::set_hanging_anim( anim a )
{
	_hanging_anim = a;
}

void anim_handler::set_override_anim( anim* a )
{
	_current_anim = a;
	a->reset();
	_override_anim_active = true;
}
