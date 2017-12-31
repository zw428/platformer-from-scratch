#include "attack.h"
#include "attackable.h"
#include "box_object.h"
#include "box.h"
#include "knockback.h"

attack::attack()
	:_damage(0),
	 _knockback(0),
	 _owner(0)
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

bool attack::perform( attackable* a )
{
	return perform( a, 0 );
}

bool attack::perform( attackable* a, box* source )
{
	bool attacked_target = false;

	if ( a == owner() )
	{
		return false;
	}

	if ( a )
	{
		a->receive_attack( *this );
		play_sound();
		attacked_target = true;

		if ( source )
		{
			::knockback(a, *source, *this);
		}
	}


	return attacked_target;
}
