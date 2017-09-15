#include "catch.h"
#include "../block.h"

TEST_CASE( "block can be made solid/empty", "[block]" )
{
	block b;

	b.type(empty);

	REQUIRE( b.is_solid() == false );

	b.type(solid);

	REQUIRE( b.is_solid() == true );
}
