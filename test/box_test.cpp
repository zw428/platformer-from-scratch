#include "catch.h"
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

TEST_CASE( "box position helpers work", "[box]" )
{
	box b;

	b.x(10);
	b.y(20);
	b.w(30);
	b.h(40);

	CHECK( b.x_center() == 25 );
	CHECK( b.y_center() == 40 );
	CHECK( b.left() == 10 );
	CHECK( b.right() == 40 );
	CHECK( b.top() == 20 );
	CHECK( b.bottom() == 60 );
}
