#include "collide_functions.h"

bool box_in_box( unsigned x1, unsigned y1, unsigned w1, unsigned h1, unsigned x2, unsigned y2, unsigned w2, unsigned h2 )
{
	if ( !w1 || !h1 || !w2 || !h2 )
	{
		return false;
	}

	return ( x1 < x2 + w2 && x1 + w1 > x2 && y1 + h1 > y2 && y1 < y2 + h2 );
}
