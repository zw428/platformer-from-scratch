#include "box_object.h"
#include "collider.h"

box_object::box_object()
{
}

bool box_object::think()
{
	handle_speeds(speeds, this);

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
