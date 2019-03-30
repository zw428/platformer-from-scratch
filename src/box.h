#pragma once

#ifndef BOX_H
#define BOX_H

#include "coords.h"

class box : public coords
{
public:
	box();

	void w( unsigned short w);
	void h( unsigned short h);

	unsigned short w() const;
	unsigned short h() const;

	unsigned short x_center() const;
	unsigned short y_center() const;

	unsigned short top() const;
	unsigned short bottom() const;
	unsigned short left() const;
	unsigned short right() const;
private:
	unsigned short _w;
	unsigned short _h;
};

#endif
