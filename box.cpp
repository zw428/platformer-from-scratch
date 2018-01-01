#include "box.h"

box::box()
	:_w(16),
	 _h(16)
{
}

void box::w( unsigned short w)
{
	_w = w;
}

void box::h( unsigned short h)
{
	_h = h;
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
	return x() + _w / 2;
}

unsigned short box::y_center() const
{
	return y() + _h / 2;
}

unsigned short box::top() const
{
	return y();
}

unsigned short box::bottom() const
{
	return y() + _h;
}

unsigned short box::left() const
{
	return x();
}

unsigned short box::right() const
{
	return x() + _w;
}
