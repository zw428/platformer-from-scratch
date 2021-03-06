#include "teleport_box.h"
#include "teleporter.h"

teleport_box::teleport_box()
	:trigger(),
	 _x_dest(0),
	 _y_dest(0)
{
	lifespan(0);
	interval(0);
}

teleport_box::~teleport_box()
{
}

void teleport_box::set_dest( int x, int y )
{
	_x_dest = x;
	_y_dest = y;
}

bool teleport_box::action( box_object* bo )
{
	teleport( bo, _x_dest, _y_dest );
	return false;
}
