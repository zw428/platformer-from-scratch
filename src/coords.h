#pragma once

#ifndef COORDS_H
#define COORDS_H

class coords
{
public:
	coords();
	void x( int x);
	void y( int y);

	int x() const;
	int y() const;
private:
	int _x;
	int _y;
};

#endif
