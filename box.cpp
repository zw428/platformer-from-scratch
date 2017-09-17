#include "box.h"

box::box()
	:_x(0),
	 _y(0),
	 _w(16),
	 _h(16)
{
}

void box::x( unsigned short x)
{
	_x = x;
}

void box::y( unsigned short y)
{
	_y = y;
}

void box::w( unsigned short w)
{
	_w = w;
}

void box::h( unsigned short h)
{
	_h = h;
}

unsigned short box::x() const
{
	return _x;
}

unsigned short box::y() const
{
	return _y;
}

unsigned short box::w() const
{
	return _w;
}

unsigned short box::h() const
{
	return _h;
}

unsigned short box::x_center() const
{
	return _x + _w / 2;
}

unsigned short box::y_center() const
{
	return _y + _h / 2;
}

unsigned short box::top() const
{
	return _y;
}

unsigned short box::bottom() const
{
	return _y + _h;
}

unsigned short box::left() const
{
	return _x;
}

unsigned short box::right() const
{
	return _x + _w;
}
