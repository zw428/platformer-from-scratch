#include "catch.h"
#include "../friction.h"

TEST_CASE( "friction::friction_reduction gives how much to subtract from h_speed", "[friction]" )
{
	friction f;
	f.coefficient(0.5);

	CHECK( f.friction_reduction( 5 ) == 0.5 );
}
