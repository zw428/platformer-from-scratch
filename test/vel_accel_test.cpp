#include "catch.h"
#include "../vel_accel.h"

TEST_CASE( "vel_accel setters/getters work", "[vel_accel]" )
{
	vel_accel v;

	v.h_speed(5);
	v.v_speed(6);
	v.h_accel(7);
	v.v_accel(8);

	CHECK( v.h_speed() == 5);
	CHECK( v.v_speed() == 6);
	CHECK( v.h_accel() == 7);
	CHECK( v.v_accel() == 8);
}

TEST_CASE( "vel_accel limits speed", "[vel_accel]" )
{
	SECTION( "positive" )
	{
		vel_accel v;

		v.h_speed(25);
		v.v_speed(25);

		CHECK( v.h_speed() == 15);
		CHECK( v.v_speed() == 15);
	}

	SECTION( "negative" )
	{
		vel_accel v;

		v.h_speed(-25);
		v.v_speed(-25);

		CHECK( v.h_speed() == -15);
		CHECK( v.v_speed() == -15);
	}
}
