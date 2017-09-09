#include "catch.hpp"
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

TEST_CASE( "gravity_affected causes vertical acceleration", "[gravity_affected]" )
{
	gravity_affected g;

	CHECK( g.v_accel() == 0 );

	g.handle_gravity();

	CHECK( g.v_accel() == GRAVITY_ACCEL );
}
