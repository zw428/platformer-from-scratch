#include "knockback.h"
#include "knockback_mult.h"
#include "object.h"
#include "box.h"
#include "vel_accel.h"

void knockback( object* obj, box* source, const attack& att )
{
	if ( dynamic_cast<attackable*>(obj) == att.owner() )
	{
		return;
	}

	vel_accel* va = dynamic_cast<vel_accel*>( obj );

	if ( !va )
	{
		return;
	}

	float x_diff = obj->x_center() - source->x_center();
	float y_diff = obj->y_center() - source->y_center();

	float x_frac = std::abs(x_diff) / (std::abs(x_diff) + std::abs(y_diff));
	float y_frac = std::abs(y_diff) / (std::abs(x_diff) + std::abs(y_diff));

	if ( x_diff < 0 )
	{
		x_frac *= -1;
	}

	if ( y_diff < 0 )
	{
		y_frac *= -1;
	}

	float mult = 1;

	knockback_mult* k = dynamic_cast<knockback_mult*>(obj);

	if ( k )
	{
		mult = k->get_knockback_mult();
	}

	va->h_speed( float(att.knockback()) * x_frac * mult );
	va->v_speed( float(att.knockback()) * y_frac * mult );
}
