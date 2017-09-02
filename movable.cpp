#include "movable.h"

movable::movable()
	:_h_speed(0),
	 _v_speed(0)
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
