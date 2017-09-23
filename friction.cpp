#include "friction.h"

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

float friction::friction_reduction( float speed )
{
	float target_speed = speed;

	if ( speed > 0 )
	{
		target_speed -= coefficient();
	}
	else if ( speed < 0 )
	{
		target_speed += coefficient();
	}

	if ( target_speed * speed < 0 )
	{
		target_speed = 0;
	}

	return speed - target_speed;
}
