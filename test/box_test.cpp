#include "catch.hpp"
#include "../box.h"

TEST_CASE( "box setters and getters work", "[box]" )
{
	box b;

	b.x(1);
	b.y(2);
	b.w(3);
	b.h(4);

	SECTION( "non-const box" )
	{
		box& b_nonconst = b;

		REQUIRE( b_nonconst.x() == 1 );
		REQUIRE( b_nonconst.y() == 2 );
		REQUIRE( b_nonconst.w() == 3 );
		REQUIRE( b_nonconst.h() == 4 );
	}

	SECTION( "const box" )
	{
		const box& b_const = b;

		REQUIRE( b_const.x() == 1 );
		REQUIRE( b_const.y() == 2 );
		REQUIRE( b_const.w() == 3 );
		REQUIRE( b_const.h() == 4 );
	}
}
