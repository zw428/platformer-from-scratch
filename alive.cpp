#include "alive.h"

alive::alive()
{
	_health = 1;
}

void alive::receive_attack( const attack& att )
{
	short health_diff = int(att.damage()) - _armor;

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
