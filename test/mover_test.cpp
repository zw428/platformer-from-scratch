#include "catch.h"
#include "../mover.h"
#include "../vel_accel.h"

TEST_CASE( "mover::move_* limited by h_speed_max", "[mover]" )
{
	SECTION( "right" )
	{
		mover m;
		m.h_speed_max(10);
		m.h_accel_rate(2);

		vel_accel va;
		va.h_speed(9);

		m.move_right(va);


		CHECK( va.h_speed() == 10 );

		m.move_left(va);

		CHECK( va.h_speed() == 8 );
	}

	SECTION( "left" )
	{
		mover m;
		m.h_speed_max(10);
		m.h_accel_rate(2);

		vel_accel va;
		va.h_speed(-9);

		m.move_left(va);

		CHECK( va.h_speed() == -10 );

		m.move_right(va);

		CHECK( va.h_speed() == -8 );
	}
}

TEST_CASE( "mover::move_* changes direction facing", "[mover]" )
{
	mover m;
	vel_accel va;

	m.move_left(va);
	CHECK( m.facing_left() == true );
	CHECK( m.facing_right() == false );

	m.move_right(va);
	CHECK( m.facing_right() == true );
	CHECK( m.facing_left() == false );
}
