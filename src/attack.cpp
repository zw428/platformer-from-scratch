#include "attack.h"
#include "attackable.h"
#include "box_object.h"
#include "box.h"
#include "knockback.h"

attack::attack()
	:_damage(0),
	 _knockback(0),
	 _hit_angle(0),
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

double attack::hit_angle() const
{
	return _hit_angle;
}

void attack::hit_angle(double ang)
{
	_hit_angle = ang;
}

void attack::owner( attackable* own )
{
	_owner = own;
}

bool attack::perform( attackable* a, double hit_angle )
{
	bool attacked_target = false;

	if ( a == owner() )
	{
		return false;
	}

	if ( a )
	{
		play_sound();
		attacked_target = true;

		::knockback(a, hit_angle, *this);

		a->receive_attack( *this );
	}

	return attacked_target;
}
