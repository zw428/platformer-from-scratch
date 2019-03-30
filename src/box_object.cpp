#include "box_object.h"
#include "collider.h"

box_object::box_object()
	:_solid(true),
	 _movable(true),
	 _die_oob(false),
	 _die_on_collide(false)
{
}

bool box_object::think_more()
{
	for ( unsigned i=0; i < children_size(); i++ )
	{
		box_object* bo = dynamic_cast<box_object*>(child_at_index(i));

		if ( bo )
		{
			bo->speeds = speeds;
			bo->speeds.h_accel(0);
			bo->speeds.v_accel(0);
		}
	}

	if ( movable() )
	{
		if ( !handle_speeds(speeds, this) && die_on_collide() )
		{
			return true;
		}
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

bool box_object::die_on_collide() const
{
	return _die_on_collide;
}

void box_object::die_on_collide( bool doc )
{
	_die_on_collide = doc;
}
