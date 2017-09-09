#include "catch.hpp"
#include "../chunk_prop.h"

TEST_CASE( "chunk_prop x and y can be set", "[chunk_prop]" )
{
	chunk_prop cp;
	cp.x = 5;
	cp.y = 7;

	CHECK( cp.x == 5 );
	CHECK( cp.y == 7 );
}

TEST_CASE( "chunk_prop can be compared for equality", "[chunk_prop]" )
{
	chunk_prop cp1;
	chunk_prop cp2;

	cp1.x = 3;
	cp1.y = 4;

	cp2.x = 5;
	cp2.y = 6;

	CHECK( cp1 != cp2 );
	
	cp2.x = cp1.x;
	cp2.y = cp1.y;

	CHECK( cp1 == cp2 );
}
