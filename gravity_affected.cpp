#include "gravity_affected.h"
#include "consts.h"

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

double gravity_affected::gravity_accel( bool on_ground )
{
	if ( !weightless() && !on_ground )
	{
		return GRAVITY_ACCEL;
	}

	return 0;
}
