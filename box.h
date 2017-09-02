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
private:
	unsigned short _x;
	unsigned short _y;
	unsigned short _w;
	unsigned short _h;
};

#endif
