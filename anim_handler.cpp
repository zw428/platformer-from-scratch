#include "anim_handler.h"

anim_handler::anim_handler()
	:_current_anim(0)
{
}

void anim_handler::think( bool on_ground, bool facing_left, bool moving, bool disabled )
{
	if ( disabled )
	{
		_current_anim = &_disabled_anim;
		_current_anim->flip_h( facing_left );
		return;
	}

	if ( on_ground && !moving )
	{
		_current_anim = &_idle_anim;
		_current_anim->flip_h( facing_left );
		return;
	}

	if ( on_ground && moving )
	{
		_current_anim = &_running_anim;
		_current_anim->flip_h( facing_left );
		return;
	}

	if ( !on_ground && moving )
	{
		_current_anim = &_jumping_anim;
		_current_anim->flip_h( facing_left );
		return;
	}

	if ( !_current_anim )
	{
		_current_anim = &_idle_anim;
		_current_anim->flip_h( facing_left );
	}
}

anim* anim_handler::current_anim()
{
	return _current_anim;
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
