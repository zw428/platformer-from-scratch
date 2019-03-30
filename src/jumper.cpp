#include "jumper.h"

jumper::jumper()
	:_jump_vel_1(9),
	 _jump_vel_2(8),
	 _times_jumped(0),
	 _jump_released(true)

{
}

void jumper::jump_vel_1( float speed )
{
	_jump_vel_1 = speed;
}

void jumper::jump_vel_2( float speed )
{
	_jump_vel_2 = speed;
}

float jumper::jump_vel_1() const
{
	return _jump_vel_1;
}

float jumper::jump_vel_2() const
{
	return _jump_vel_2;
}

unsigned short jumper::times_jumped() const
{
	return _times_jumped;
}

short jumper::jump( bool first )
{
	if ( _times_jumped == 2 || !_jump_released )
	{
		return 0;
	}

	_jump_released = false;

	if ( first )
	{
		_times_jumped = 1;
		return -jump_vel_1();
	}
	else
	{
		_times_jumped = 2;
		return -jump_vel_2();
	}
}

short jumper::handle_jumping( bool on_ground, bool jumping )
{
	if ( !jumping )
	{
		_jump_released = true;
	}

	if ( jumping )
	{
		return jump( on_ground );
	}
	else if ( on_ground )
	{
		_times_jumped = 0;
	}
	else if ( _times_jumped == 0 )
	{
		_times_jumped = 1;
	}

	return 0;
}
