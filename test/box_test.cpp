#include "catch.hpp"
#include "../box.h"

TEST_CASE( "box setters and getters work", "[box]" )
{
	box b;

	b.x(1);
	b.y(2);
	b.w(3);
	b.h(4);

	CHECK( b.x() == 1 );
	CHECK( b.y() == 2 );
	CHECK( b.w() == 3 );
	CHECK( b.h() == 4 );
}
