#include "attack_box.h"
#include "attackable.h"
#include "knockback.h"
#include "object.h"

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
	attackable* a = dynamic_cast<attackable*>(obj);

	if ( !a )
	{
		return false;
	}

	_attack.perform( a );

	box* b = dynamic_cast<box*>(_attack.owner());

	if ( !b )
	{
		b = this;
	}

	knockback( obj, b, _attack );

	return false;
}
