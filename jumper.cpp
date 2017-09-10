#include "jumper.h"

jumper::jumper()
	:gravity_affected(),
	 _jump_vel_1(9),
	 _jump_vel_2(8),
	 _times_jumped(0),
	 _jump_released(true)

{
}

void jumper::jump_vel_1( unsigned short speed )
{
	_jump_vel_1 = speed;
}

void jumper::jump_vel_2( unsigned short speed )
{
	_jump_vel_2 = speed;
}

unsigned short jumper::jump_vel_1() const
{
	return _jump_vel_1;
}

unsigned short jumper::jump_vel_2() const
{
	return _jump_vel_2;
}

unsigned short jumper::times_jumped() const
{
	return _times_jumped;
}

void jumper::jump( bool first )
{
	if ( _times_jumped == 2 || !_jump_released )
	{
		return;
	}

	_jump_released = false;

	if ( first )
	{
		v_speed( -jump_vel_1() );
		_times_jumped = 1;
	}
	else
	{
		v_speed( -jump_vel_2() );
		_times_jumped = 2;
	}
}

void jumper::handle_jumping( bool jumping )
{
	bool on_ground = colliding(2);

	if ( !jumping )
	{
		_jump_released = true;
	}

	if ( jumping )
	{
		jump( on_ground );
	}
	else if ( on_ground )
	{
		_times_jumped = 0;
	}
	else if ( _times_jumped == 0 )
	{
		_times_jumped = 1;
	}
}
