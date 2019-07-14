#include "attack_box.h"
#include "attackable.h"
#include "object.h"
#include "creature.h"

attack_box::attack_box()
	:trigger()
{
	lifespan(20);
	interval(20);
	enabled(true);
	die_on_collide(false);
}

attack_box::~attack_box()
{
}

void attack_box::set_attack( attack att )
{
	_attack = att;
}

bool attack_box::action(box_object* bo)
{
	attackable* a = dynamic_cast<attackable*>(bo);

	if ( !a )
	{
		return false;
	}

	double hit_angle = _attack.hit_angle();

	if ( speeds.h_speed() < 0 )
	{
		hit_angle += 180 - hit_angle*2;
	}

	_attack.perform( a, hit_angle );

	return false;
}
