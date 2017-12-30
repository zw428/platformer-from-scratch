#include "gravity_affected.h"
#include "consts.h"
#include "vel_accel.h"

gravity_affected::gravity_affected()
	:_weightless(false)
{
}

bool gravity_affected::weightless() const
{
	return _weightless;
}

void gravity_affected::weightless(bool weightless)
{
	_weightless = weightless;
}

void gravity_affected::apply_gravity(vel_accel* va, bool on_ground)
{
	if ( !weightless() && !on_ground )
	{
		va->v_accel( GRAVITY_ACCEL );
	}
}
