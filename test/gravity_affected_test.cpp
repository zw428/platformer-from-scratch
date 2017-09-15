#include "catch.h"
#include "../gravity_affected.h"
#include "../consts.h"

TEST_CASE( "gravity_affected constructor initializes stuff", "[gravity_affected]" )
{
	gravity_affected g;

	CHECK( g.weightless() == false );
}

TEST_CASE( "gravity_affected setters/getters work", "[gravity_affected]" )
{
	gravity_affected g;

	g.weightless(true);

	CHECK( g.weightless() == true );
}

TEST_CASE( "gravity_affected accelerates if not weightless and not on ground", "[gravity_affected]" )
{
	gravity_affected g;

	CHECK( g.gravity_accel(true) == 0 );

	CHECK( g.gravity_accel(false) == GRAVITY_ACCEL );
}
