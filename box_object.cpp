#include "box_object.h"
#include "collider.h"

box_object::box_object()
	:_solid(true),
	 _movable(true)
{
}

bool box_object::think()
{
	if ( movable() )
	{
		handle_speeds(speeds, this);
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
