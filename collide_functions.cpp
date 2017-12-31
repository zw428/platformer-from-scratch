#include "collide_functions.h"
#include "box.h"

bool box_in_box( unsigned x1, unsigned y1, unsigned w1, unsigned h1, unsigned x2, unsigned y2, unsigned w2, unsigned h2 )
{
	if ( !w1 || !h1 || !w2 || !h2 )
	{
		return false;
	}

	return ( x1 < x2 + w2 && x1 + w1 > x2 && y1 + h1 > y2 && y1 < y2 + h2 );
}

bool box_in_box( box b1, box b2 )
{
	return box_in_box( b1.x(), b1.y(), b1.w(), b1.h(), b2.x(), b2.y(), b2.w(), b2.h() );
}
