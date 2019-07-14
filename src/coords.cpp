#include "coords.h"

coords::coords()
	:_x(0),
	 _y(0)
{
}

void coords::x( int x)
{
	_x = x;
}

void coords::y( int y)
{
	_y = y;
}


int coords::x() const
{
	return _x;
}

int coords::y() const
{
	return _y;
}
