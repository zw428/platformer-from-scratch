#include "catch.h"
#include "../attack_box.h"
#include "../box_object.h"
#include "../vel_accel.h"
#include "../knockback.h"
#include "../alive.h"

TEST_CASE( "knockback() will move object", "[knockback]" )
{
	box_object t;

	t.speeds.h_speed(0);
	t.speeds.v_speed(0);

	attack a;
	a.knockback(5);

	box b;

	b.x( t.dimens.x() + 1 );
	b.y( t.dimens.y() + 1 );
	b.w( t.dimens.w() + 1 );
	b.h( t.dimens.h() + 1 );

	knockback( dynamic_cast<box_object*>(&t), b, a );

	CHECK( t.speeds.h_speed() != 0 );
	CHECK( t.speeds.v_speed() != 0 );
}

TEST_CASE( "knockback() will knockback object in a certain direction", "[knockback]" )
{
	SECTION( "from left" )
	{
		box_object t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.dimens.x() - b.w() );
		b.y( t.dimens.y() );
		b.w( 50 );
		b.h( 50 );

		knockback( dynamic_cast<box_object*>(&t), b, a );

		CHECK( t.speeds.h_speed() > 0 );
	}

	SECTION( "from right" )
	{
		box_object t;

		t.speeds.h_speed(0);
		t.speeds.v_speed(0);
		t.dimens.x(200);
		t.dimens.y(200);
		t.dimens.w(50);
		t.dimens.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.dimens.right() );
		b.y( t.dimens.y() );
		b.w( 50 );
		b.h( 50 );

		knockback( dynamic_cast<box_object*>(&t), b, a );

		CHECK( t.speeds.h_speed() < 0 );
	}

	SECTION( "from top" )
	{
		box_object t;

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
		b.y( t.dimens.y() - b.h() );
		b.w(  50 );
		b.h(  50 );

		knockback( dynamic_cast<box_object*>(&t), b, a );

		CHECK( t.speeds.v_speed() > 0 );
	}

	SECTION( "from bottom" )
	{
		box_object t;

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

		knockback( dynamic_cast<box_object*>(&t), b, a );

		CHECK( t.speeds.v_speed() < 0 );
	}
}
