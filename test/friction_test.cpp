#include "catch.h"
#include "../friction.h"
#include "../vel_accel.h"

TEST_CASE( "friction::friction_reduction gives how much to subtract from h_speed", "[friction]" )
{
	vel_accel va;

	va.h_speed(5);

	friction f;
	f.coefficient(0.5);

	f.apply_friction(va);

	CHECK( va.h_speed() == 4.5 );
}
