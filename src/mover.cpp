#include "mover.h"
#include "vel_accel.h"

mover::mover()
	:_h_speed_max(5),
	 _h_accel_rate(1),
	 _facing_right(true)
{
}

unsigned short mover::h_speed_max() const
{
	return _h_speed_max;
}

void mover::h_speed_max( float speed )
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

void mover::move_left( vel_accel& va )
{
	float h_speed = va.h_speed();
	_facing_right = false;

	float new_speed = h_speed;

	if ( h_speed > -h_speed_max() )
	{
		float desired_speed = h_speed - h_accel_rate();

		if ( desired_speed >= -h_speed_max() )
		{
			new_speed = desired_speed;
		}
		else
		{
			new_speed = -h_speed_max();
		}
	}

	va.h_speed(new_speed);
}

void mover::move_right( vel_accel& va )
{
	float h_speed = va.h_speed();
	_facing_right = true;

	float new_speed = h_speed;

	if ( h_speed < h_speed_max() )
	{
		float desired_speed = h_speed + h_accel_rate();

		if ( desired_speed <= h_speed_max() )
		{
			new_speed = desired_speed;
		}
		else
		{
			new_speed = h_speed_max();
		}
	}

	va.h_speed(new_speed);
}

void mover::face_left()
{
	_facing_right = false;
}

void mover::face_right()
{
	_facing_right = true;
}

bool mover::facing_left() const
{
	return !_facing_right;
}

bool mover::facing_right() const
{
	return _facing_right;
}
