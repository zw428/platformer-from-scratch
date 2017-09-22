#include "catch.h"
#include "../attack_box.h"
#include "../object.h"
#include "../alive.h"
#include "../vel_accel.h"
#include "../knockback.h"

class knockback_tmp : public object, public vel_accel
{
	bool think() { return false; };
};

TEST_CASE( "knockback() will move object", "[knockback]" )
{
	knockback_tmp t;

	t.h_speed(0);
	t.v_speed(0);

	attack a;
	a.knockback(5);

	box b;

	b.x( t.x() + 1 );
	b.y( t.y() + 1 );
	b.w( t.w() + 1 );
	b.h( t.h() + 1 );

	knockback( dynamic_cast<object*>(&t), &b, a );

	CHECK( t.h_speed() != 0 );
	CHECK( t.v_speed() != 0 );
}

TEST_CASE( "knockback() will knockback object in a certain direction", "[knockback]" )
{
	SECTION( "from left" )
	{
		knockback_tmp t;

		t.h_speed(0);
		t.v_speed(0);
		t.x(200);
		t.y(200);
		t.w(50);
		t.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.x() - b.w() );
		b.y( t.y() );
		b.w( 50 );
		b.h( 50 );

		knockback( dynamic_cast<object*>(&t), &b, a );

		CHECK( t.h_speed() > 0 );
	}

	SECTION( "from right" )
	{
		knockback_tmp t;

		t.h_speed(0);
		t.v_speed(0);
		t.x(200);
		t.y(200);
		t.w(50);
		t.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.right() );
		b.y( t.y() );
		b.w( 50 );
		b.h( 50 );

		knockback( dynamic_cast<object*>(&t), &b, a );

		CHECK( t.h_speed() < 0 );
	}

	SECTION( "from top" )
	{
		knockback_tmp t;

		t.h_speed(0);
		t.v_speed(0);
		t.x(200);
		t.y(200);
		t.w(50);
		t.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.x() );
		b.y( t.y() - b.h() );
		b.w(  50 );
		b.h(  50 );

		knockback( dynamic_cast<object*>(&t), &b, a );

		CHECK( t.v_speed() > 0 );
	}

	SECTION( "from bottom" )
	{
		knockback_tmp t;

		t.h_speed(0);
		t.v_speed(0);
		t.x(200);
		t.y(200);
		t.w(50);
		t.h(50);

		attack a;
		a.knockback(5);

		box b;

		b.x( t.x() );
		b.y( t.bottom() );
		b.w(  50 );
		b.h(  50 );

		knockback( dynamic_cast<object*>(&t), &b, a );

		CHECK( t.v_speed() < 0 );
	}
}
