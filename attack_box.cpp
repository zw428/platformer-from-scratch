#include "attack_box.h"
#include "attackable.h"
#include "knockback_mult.h"
#include "object.h"
#include "vel_accel.h"

class object;

attack_box::attack_box()
	:trigger()
{
	lifespan(20);
	interval(20);
}

attack_box::~attack_box()
{
}

void attack_box::set_attack( attack att )
{
	_attack = att;
}

bool attack_box::action(object* obj)
{
	attackable* at = dynamic_cast<attackable*>(obj);

	if ( at )
	{
		_attack.perform( at );
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

	if ( va )
	{
		va->h_speed( _attack.knockback() * x_frac * mult );
		va->v_speed( _attack.knockback() * y_frac * mult );
	}

	return false;
}
