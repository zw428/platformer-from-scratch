#include "gravity_affected.h"
#include "consts.h"

gravity_affected::gravity_affected()
	:collider()
{
}

bool gravity_affected::weightless()
{
	return _weightless;
}

void gravity_affected::weightless(bool weightless)
{
	_weightless = weightless;
}

void gravity_affected::handle_gravity()
{
	if ( !colliding(2) && !weightless() )
	{
		v_speed( v_speed() + GRAVITY_ACCEL );
	}
}
