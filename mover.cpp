#include "mover.h"

mover::mover()
	:_h_speed_max(5),
	 _h_accel_rate(1)
{
}

unsigned short mover::h_speed_max() const
{
	return _h_speed_max;
}

void mover::h_speed_max( unsigned short speed )
{
	_h_speed_max = speed;
}

float mover::h_accel_rate() const
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
