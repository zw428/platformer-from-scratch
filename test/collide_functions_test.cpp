#include "catch.h"
#include "../collide_functions.h"

TEST_CASE( "two apart boxes don't collide", "[collide_functions]" )
{
	CHECK( box_in_box( 0, 0, 5, 5, 10, 10, 5, 5 ) == false );
}

TEST_CASE( "two intersecting boxes collide", "[collide_functions]" )
{
	CHECK( box_in_box( 0, 0, 5, 5, 1, 1, 5, 5 ) == true );
}

TEST_CASE( "two adjacent boxes don't collide", "[collide_functions]" )
{
	CHECK( box_in_box( 0, 0, 5, 5, 5, 5, 5, 5 ) == false );
}
