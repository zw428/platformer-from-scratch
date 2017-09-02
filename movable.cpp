#include "movable.h"

movable::movable()
	:_h_speed(0),
	 _v_speed(0),
	 _h_accel(0),
	 _v_accel(0)
{
}

void movable::h_speed(float h_speed)
{
	_h_speed = h_speed;
}

void movable::v_speed(float v_speed)
{
	_v_speed = v_speed;
}

float movable::h_speed()
{
	return _h_speed;
}

float movable::v_speed()
{
	return _v_speed;
}

void movable::h_accel(float h_accel)
{
	_h_accel = h_accel;
}

void movable::v_accel(float v_accel)
{
	_v_accel = v_accel;
}

float movable::h_accel()
{
	return _h_accel;
}

float movable::v_accel()
{
	return _v_accel;
}
