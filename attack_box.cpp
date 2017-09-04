#include "attack_box.h"
#include "alive.h"
#include "object.h"
#include "knockback_mult.h"

attack_box::attack_box()
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

	unsigned short temp_x = x() + (w() / 2);
	unsigned short temp_y = y() + (h() / 2);

	double x_diff = obj->x() - temp_x;
	double y_diff = obj->y() - temp_y;

	float x_frac = x_diff / (x_diff + y_diff);
	float y_frac = y_diff / (x_diff + y_diff);

	float mult = 1;

	knockback_mult* k = dynamic_cast<knockback_mult*>(obj);

	if ( k )
	{
		mult = k->get_knockback_mult();
	}

	obj->h_speed( knockback() * x_frac * mult );
	obj->v_speed( knockback() * y_frac * mult );

	return false;
}
