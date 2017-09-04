#include "attack.h"
#include "manager.h"
#include "alive.h"

attack::attack()
	:_damage(0),
	 _knockback(0)
{
}

void attack::damage( unsigned short damage )
{
	_damage = damage;
}

unsigned short attack::damage() const
{
	return _damage;
}

void attack::knockback( unsigned short knockback )
{
	_knockback = knockback;
}

unsigned short attack::knockback() const
{
	return _knockback;
}

alive* attack::owner()
{
	return _owner;
}

void attack::owner( alive* own )
{
	_owner = own;
}

void attack::perform( alive* al )
{
	al->receive_attack( *this );
	play_sound();
}
