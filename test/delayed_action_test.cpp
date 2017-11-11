#include "catch.h"
#include "../delayed_action.h"

TEST_CASE( "delayed_action cooldown/delay minimize at 2", "[delayed_action]" )
{
	delayed_action d;

	d.delay(0);
	d.cooldown(0);

	CHECK(d.delay() == 2);
	CHECK(d.cooldown() == 2);
}

TEST_CASE( "delayed_action is ready after a delay", "[delayed_action]" )
{
	delayed_action d;
	d.delay(5);

	CHECK( d.ready() == false );

	d.think(false);

	CHECK( d.acting() == false );

	for ( unsigned i=0; i < 4; i++ )
	{
		d.think(true);
		CHECK( d.ready() == false );
	}

	d.think(true);

	CHECK( d.ready() == true );

	d.think(true);

	CHECK( d.ready() == false );
}

TEST_CASE( "delayed_action isn't ready until cooldown is over", "[delayed_action]" )
{
	delayed_action d;
	d.delay(5);
	d.cooldown(10);

	for ( unsigned i=0; i < 4; i++ )
	{
		d.think(true);
	}

	d.think(true);

	CHECK( d.ready() == true );

	d.think(true);

	CHECK( d.ready() == false );

	for ( unsigned i=0; i < 8; i++ )
	{
		d.think(true);
		CHECK( d.ready() == false );
	}

	d.think(true);
	CHECK( d.ready() == true );
}
