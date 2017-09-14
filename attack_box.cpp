#include "attack_box.h"
#include "alive.h"
#include "object.h"
#include "knockback_mult.h"
#include "npc.h"
#include "vel_accel.h"

attack_box::attack_box()
	:trigger()
{
	lifespan(20);
	interval(20);
}

attack_box::~attack_box()
{
}

bool attack_box::action(object* obj)
{
	alive* al = dynamic_cast<alive*>(obj);

	if ( al && al != owner() )
	{
		perform( al );
	}

	float temp_x = float(x()) + (float(w()) / 2);
	float temp_y = float(y()) + (float(h()) / 2);

	float x_diff = float(obj->x()) - temp_x;
	float y_diff = float(obj->y()) - temp_y;

	float x_frac = 1 - x_diff / (std::abs(x_diff) + std::abs(y_diff));
	float y_frac = 1 - y_diff / (std::abs(x_diff) + std::abs(y_diff));

	float mult = 1;

	knockback_mult* k = dynamic_cast<knockback_mult*>(obj);

	if ( k )
	{
		mult = k->get_knockback_mult();
	}

	vel_accel* va = dynamic_cast<vel_accel*>( obj );

	va->h_speed( knockback() * x_frac * mult );
	va->v_speed( knockback() * y_frac * mult );

	return false;
}
