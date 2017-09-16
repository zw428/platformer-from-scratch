#include "attack.h"
#include "attackable.h"

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

attackable* attack::owner() const
{
	return _owner;
}

void attack::owner( attackable* own )
{
	_owner = own;
}

void attack::perform( attackable* a )
{
	a->receive_attack( *this );
	play_sound();
}
