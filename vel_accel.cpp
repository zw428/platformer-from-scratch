#include "vel_accel.h"

vel_accel::vel_accel()
	:_h_speed(0),
	 _v_speed(0),
	 _h_accel(0),
	 _v_accel(0)
{
}

void vel_accel::h_speed(float h_speed)
{
	_h_speed = h_speed;
}

void vel_accel::v_speed(float v_speed)
{
	_v_speed = v_speed;
}

float vel_accel::h_speed()
{
	return _h_speed;
}

float vel_accel::v_speed()
{
	return _v_speed;
}

void vel_accel::h_accel(float h_accel)
{
	_h_accel = h_accel;
}

void vel_accel::v_accel(float v_accel)
{
	_v_accel = v_accel;
}

float vel_accel::h_accel()
{
	return _h_accel;
}

float vel_accel::v_accel()
{
	return _v_accel;
}
