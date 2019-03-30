#pragma once

#ifndef COORDS_H
#define COORDS_H

class coords
{
public:
	coords();
	void x( unsigned short x);
	void y( unsigned short y);

	unsigned short x() const;
	unsigned short y() const;
private:
	unsigned short _x;
	unsigned short _y;
};

#endif
