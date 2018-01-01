#include "coords.h"

coords::coords()
	:_x(0),
	 _y(0)
{
}

void coords::x( unsigned short x)
{
	_x = x;
}

void coords::y( unsigned short y)
{
	_y = y;
}


unsigned short coords::x() const
{
	return _x;
}

unsigned short coords::y() const
{
	return _y;
}
