#include "box_object.h"
#include "collider.h"

box_object::box_object()
	:_solid(true),
	 _movable(true),
	 _die_oob(false)
{
}

bool box_object::think()
{
	if ( movable() )
	{
		handle_speeds(speeds, this);
	}

	if ( die_oob() && on_map_edge(dimens) )
	{
		return true;
	}

	return false;
}

bool box_object::solid() const
{
	return _solid;
}

void box_object::solid( bool solid )
{
	_solid = solid;
}

bool box_object::movable() const
{
	return _movable;
}

void box_object::movable( bool movable )
{
	_movable = movable;
}

bool box_object::die_oob() const
{
	return _die_oob;
}

void box_object::die_oob( bool d_o )
{
	_die_oob = d_o;
}
