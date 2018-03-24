#include "attack_box.h"
#include "attackable.h"
#include "object.h"

attack_box::attack_box()
	:trigger()
{
	lifespan(20);
	interval(20);
	enabled(true);
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

	_attack.perform( a, &dimens );

	return false;
}
