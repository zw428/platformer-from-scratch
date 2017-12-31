#include "attackable.h"
#include <SDL2/SDL.h>

attackable::attackable()
	 :_at(attackable_health),
	 _health(1)
{
}

attackable::~attackable()
{
}

void attackable::receive_attack( const attack& att )
{
	switch( _at )
	{
		case attackable_invincible:
			return;
			break;
		case attackable_health:
			attacked_health( att );
			break;
		case attackable_knockback_multiplier:
			attacked_knockback_multiplier( att );
			break;
	}
}

bool attackable::think()
{
	return box_object::think();
}

void attackable::health( unsigned short health )
{
	_health = health;
}

unsigned short attackable::health() const
{
	return _health;
}

void attackable::type( attackable_type t )
{
	_at = t;
}

attackable_type attackable::type() const
{
	return _at;
}

void attackable::attacked_health( const attack& att )
{
	short health_diff = int(att.damage());

	if ( health_diff > _health )
	{
		_health = 0;
	}
	else if ( health_diff > 0 )
	{
		_health -= health_diff;
	}
}

void attackable::attacked_knockback_multiplier( const attack& att )
{
	_health += att.damage();
}
