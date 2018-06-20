#include "catch.h"
#include "../attack_box.h"
#include "../box_object.h"
#include "../vel_accel.h"
#include "../knockback.h"
#include "../attackable.h"

TEST_CASE( "knockback() will move object", "[knockback]" )
{
	attackable t;

	t.speeds.h_speed(0);
	t.speeds.v_speed(0);

	attack a;
	a.knockback(5);

	knockback( &t, 0, a );

	CHECK( t.speeds.h_speed() != 0 );
	CHECK( t.speeds.v_speed() != 0 );
}

TEST_CASE( "knockback() will knockback object in a certain direction", "[knockback]" )
{
	SECTION( "from left" )
	{
		attackable t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		knockback( &t, 0, a );

		CHECK( t.speeds.h_speed() > 0 );
	}

	SECTION( "from right" )
	{
		attackable t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		knockback( &t, 180, a );

		CHECK( t.speeds.h_speed() < 0 );
	}

	SECTION( "from top" )
	{
		attackable t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		knockback( &t, 90, a );

		CHECK( t.speeds.v_speed() > 0 );
	}

	SECTION( "from bottom" )
	{
		attackable t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.dimens.x() );
		b.y( t.dimens.bottom() );
		b.w(  50 );
		b.h(  50 );

		knockback( &t, -90, a );

		CHECK( t.speeds.v_speed() < 0 );
	}
}
