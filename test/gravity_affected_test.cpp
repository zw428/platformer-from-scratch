#include <catch2/catch.hpp>
#include "gravity_affected.h"
#include "vel_accel.h"
#include "consts.h"

TEST_CASE( "gravity_affected accelerates if not weightless and not on ground", "[gravity_affected]" )
{
	vel_accel va;

	gravity_affected g;

	g.apply_gravity(va, true);

	CHECK( va.v_speed() == 0 );

	g.apply_gravity(va, false);

	CHECK( float(va.v_accel()) == float(GRAVITY_ACCEL) );
}
