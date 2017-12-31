#include "knockback.h"
#include "box.h"
#include "box_object.h"
#include "attackable.h"

void knockback( attackable* atbl, box source, const attack& att )
{
	vel_accel& va = atbl->speeds;
	box& dimens = atbl->dimens;

	float x_diff = dimens.x_center() - source.x_center();
	float y_diff = dimens.y_center() - source.y_center();

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

	if ( atbl->type() == attackable_knockback_multiplier )
	{
		mult = 1 + atbl->health() / 20;
	}

	va.h_speed( float(att.knockback()) * x_frac * mult );
	va.v_speed( float(att.knockback()) * y_frac * mult );
}
