#include "anim_handler.h"

anim_handler::anim_handler()
	:_origin(4),
	 _flipped(false)
{
}

void anim_handler::think( bool on_ground, bool facing_left, bool moving, bool hanging, bool disabled )
{
	_flipped = facing_left;

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

void anim_handler::draw( const box* ref )
{
	_current_anim->x( ref->x() );
	_current_anim->y( ref->y() );
	_current_anim->flip_h( _flipped );

	if ( _current_anim->w() != ref->w() )
	{
		switch( _origin )
		{
		case 0:
		case 4:
			_current_anim->x( ref->x_center() - _current_anim->w() / 2 );
			break;
		case 1:
		case 2:
		case 3:
			_current_anim->x( ref->right() - _current_anim->w() );
			break;
		case 5:
		case 6:
		case 7:
			_current_anim->x( ref->left() );
			break;
		}
	}

	if ( _current_anim->h() != ref->h() )
	{
		switch( _origin )
		{
		case 0:
		case 1:
		case 7:
			_current_anim->y( ref->top() );
			break;
		case 2:
		case 6:
			_current_anim->y( ref->y_center() - _current_anim->h() / 2 );
			break;
		case 3:
		case 4:
		case 5:
			_current_anim->y( ref->bottom() - _current_anim->h() );
			break;
		}
	}

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

unsigned short anim_handler::origin() const
{
	return _origin;
}

void anim_handler::origin( unsigned short origin )
{
	if ( origin < 9 )
	{
		_origin = origin;
	}
}
