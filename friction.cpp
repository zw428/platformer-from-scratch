#include "friction.h"
#include "vel_accel.h"

friction::friction()
	:_coeff(0.3)
{
}

void friction::coefficient( float coeff )
{
	_coeff = coeff;
}

float friction::coefficient()
{
	return _coeff;
}

void friction::apply_friction( vel_accel* va )
{
	float target_speed = va->h_speed();

	if ( va->h_speed() > 0 )
	{
		target_speed -= coefficient();
	}
	else if ( va->h_speed() < 0 )
	{
		target_speed += coefficient();
	}

	if ( target_speed * va->h_speed() < 0 )
	{
		target_speed = 0;
	}

	va->h_speed(target_speed);
}
