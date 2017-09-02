#include "mover.h"

mover::mover()
	:_h_speed_max(5),
	 _h_accel_rate(1),
	 _jump_vel(5)
{
}

unsigned short mover::h_speed_max()
{
	return _h_speed_max;
}

void mover::h_speed_max( unsigned short speed )
{
	_h_speed_max = speed;
}

unsigned short mover::jump_vel()
{
	return _jump_vel;
}

void mover::jump_vel( unsigned short speed )
{
	_jump_vel = speed;
}

float mover::h_accel_rate()
{
	return _h_accel_rate;
}

void mover::h_accel_rate( float rate )
{
	_h_accel_rate = rate;
}

void mover::move_left()
{
	if ( h_speed() > -h_speed_max() )
	{
		float desired_speed = h_speed() - h_accel_rate();

		if ( desired_speed >= -h_speed_max() )
		{
			h_speed( desired_speed );
		}
		else
		{
			h_speed( -h_speed_max() );
		}
	}
}

void mover::move_right()
{
	if ( h_speed() < h_speed_max() )
	{
		float desired_speed = h_speed() + h_accel_rate();

		if ( desired_speed <= h_speed_max() )
		{
			h_speed( desired_speed );
		}
		else
		{
			h_speed( h_speed_max() );
		}
	}
}

void mover::jump()
{
	v_speed( -jump_vel() );
}
