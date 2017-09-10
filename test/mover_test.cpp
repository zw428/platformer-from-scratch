#include "catch.hpp"
#include "../mover.h"

TEST_CASE( "mover constructor initializes stuff", "[mover]" )
{
	mover m;

	CHECK( m.h_speed_max() == 5 );
	CHECK( m.h_accel_rate() == 1 );
}

TEST_CASE( "mover setters/getters work", "[mover]" )
{
	mover m;

	m.h_speed_max(1);
	m.h_accel_rate(2.7);

	CHECK( m.h_speed_max() == 1 );
	CHECK( m.h_accel_rate() == float(2.7) );
}

TEST_CASE( "mover::move_* limited by h_speed_max", "[mover]" )
{
	SECTION( "right" )
	{
		mover m;
		m.h_speed_max(10);
		m.h_speed(9);
		m.h_accel_rate(2);

		m.move_right();

		CHECK( m.h_speed() == 10 );

		m.move_left();
		
		CHECK( m.h_speed() == 8 );
	}
	
	SECTION( "left" )
	{
		mover m;
		m.h_speed_max(10);
		m.h_speed(-9);
		m.h_accel_rate(2);

		m.move_left();

		CHECK( m.h_speed() == -10 );

		m.move_right();
		
		CHECK( m.h_speed() == -8 );
	}
}

TEST_CASE( "mover::move_* changes h_speed", "[mover]" )
{
	mover m;

	m.h_speed(0);
	m.move_left();
	CHECK( m.h_speed() < 0 );

	m.h_speed(0);
	m.move_right();
	CHECK( m.h_speed() > 0 );
}
