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

void friction::apply_friction()
{
	float target_speed = h_speed();

	if ( h_speed() > 0 )
	{
		target_speed -= coefficient();
	}
	else if ( h_speed() < 0 )
	{
		target_speed += coefficient();
	}

	if ( target_speed * h_speed() < 0 )
	{
		target_speed = 0;
	}

	h_speed( target_speed );
}
