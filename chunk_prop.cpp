#include "chunk_prop.h"

bool chunk_prop::operator==( const chunk_prop& cp )
{
	return ( x == cp.x && y == cp.y );
}

bool chunk_prop::operator!=( const chunk_prop& cp )
{
	return !( *this == cp );
}
