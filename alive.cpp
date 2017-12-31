#include "alive.h"

alive::alive()
	:attackable(),
	 _health(1)
{
}

alive::~alive()
{
}

void alive::receive_attack( const attack& att )
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

void alive::health( unsigned short health )
{
	_health = health;
}

unsigned short alive::health() const
{
	return _health;
}

bool on_death()
{
	return false;
}
