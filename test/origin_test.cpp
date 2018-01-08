#include "catch.h"
#include "../origin.h"

TEST_CASE( "origin::apply() can align things properly", "[origin]" )
{
	box b1;
	b1.x(50);
	b1.y(50);
	b1.w(100);
	b1.h(200);

	box b2;

	b2.w(10);
	b2.h(10);

	origin o;

	SECTION( "top" )
	{
		o.set_dir(origin_top);
		o.apply(b2, b1);
		CHECK( b2.x() == 95 );
		CHECK( b2.y() == b1.y() );
	}

	SECTION( "top right" )
	{
		o.set_dir(origin_tr);
		o.apply(b2, b1);
		CHECK( b2.x() == 140 );
		CHECK( b2.y() == b1.y() );
	}

	SECTION( "right" )
	{
		o.set_dir(origin_right);
		o.apply(b2, b1);
		CHECK( b2.x() == 140 );
		CHECK( b2.y() == 145 );
	}

	SECTION( "bottom right" )
	{
		o.set_dir(origin_br);
		o.apply(b2, b1);
		CHECK( b2.x() == 140 );
		CHECK( b2.y() == 240 );
	}

	SECTION( "bottom" )
	{
		o.set_dir(origin_bottom);
		o.apply(b2, b1);
		CHECK( b2.x() == 95 );
		CHECK( b2.y() == 240 );
	}

	SECTION( "bottom left" )
	{
		o.set_dir(origin_bl);
		o.apply(b2, b1);
		CHECK( b2.x() == 50 );
		CHECK( b2.y() == 240 );
	}

	SECTION( "left" )
	{
		o.set_dir(origin_left);
		o.apply(b2, b1);
		CHECK( b2.x() == 50 );
		CHECK( b2.y() == 145 );
	}

	SECTION( "top left" )
	{
		o.set_dir(origin_tl);
		o.apply(b2, b1);
		CHECK( b2.x() == 50 );
		CHECK( b2.y() == b1.y() );
	}

	SECTION( "center" )
	{
		o.set_dir(origin_center);
		o.apply(b2, b1);
		CHECK( b2.x() == 95 );
		CHECK( b2.y() == 145 );
	}
}
