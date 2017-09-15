#include "catch.h"
#include "../friction.h"

TEST_CASE( "friction constructor initializes correctly", "[friction]" )
{
	friction f;

	CHECK( f.coefficient() == float(0.3) );
}

TEST_CASE( "friction setters/getters work", "[friction]" )
{
	friction f;

	f.coefficient(3.2);

	CHECK( f.coefficient() == float(3.2) );
}

TEST_CASE( "friction::apply_friction slows h_speed", "[friction]" )
{
	friction f;
	f.coefficient(0.5);
	f.h_speed(5);
	f.apply_friction();

	CHECK( f.h_speed() == float(4.5) );
}

TEST_CASE( "friction::apply_friction doesn't slow v_speed", "[friction]" )
{
	friction f;
	f.coefficient(0.5);
	f.v_speed(5);
	f.apply_friction();

	CHECK( f.v_speed() == float(5) );
}
