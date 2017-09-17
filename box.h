#ifndef BOX_H
#define BOX_H

class box
{
public:
	box();

	void x( unsigned short x);
	void y( unsigned short y);
	void w( unsigned short w);
	void h( unsigned short h);

	unsigned short x() const;
	unsigned short y() const;
	unsigned short w() const;
	unsigned short h() const;

	unsigned short x_center() const;
	unsigned short y_center() const;

	unsigned short top() const;
	unsigned short bottom() const;
	unsigned short left() const;
	unsigned short right() const;
private:
	unsigned short _x;
	unsigned short _y;
	unsigned short _w;
	unsigned short _h;
};

#endif
