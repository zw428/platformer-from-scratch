#include "catch.h"
#include "../ledge_grabber.h"
#include "../manager.h"
#include "../block.h"

TEST_CASE("ledge_grabber constructor initializes stuff", "[ledge_grabber]")
{
	ledge_grabber l;
	CHECK( l.found_ledge() == false );
}

TEST_CASE("ledge_grabber gives correct distances to ledge", "[ledge_grabber]")
{
	block* ledge = new block;
	ledge->x(200);
	ledge->y(200);
	ledge->w(40);
	ledge->h(20);

	manager::instance()->get_map()->empty();
	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(ledge);

	box grabber;
	grabber.x( 245 );
	grabber.y( 190 );
	grabber.w( 20 );
	grabber.h( 20 );

	ledge_grabber l;
	l.find_ledge( &grabber );

	SECTION( "vertical" )
	{
		CHECK( l.dist_to_ledge() == 10 );
	}

	SECTION( "horizontal" )
	{
		SECTION( "left" )
		{
			CHECK( l.h_dist_to_ledge() == -5 );
		}

		SECTION( "right" )
		{
			grabber.x( 175 );
			l.find_ledge( &grabber );
			CHECK( l.h_dist_to_ledge() == 5 );
		}
	}
}

TEST_CASE("ledge_grabber finds ledge", "[ledge_grabber]")
{
	block* ledge = new block;
	ledge->x(200);
	ledge->y(200);
	ledge->w(40);
	ledge->h(20);

	manager::instance()->get_map()->empty();
	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(ledge);

	box grabber;
	grabber.x( 245 );
	grabber.y( 190 );
	grabber.w( 20 );
	grabber.h( 20 );

	ledge_grabber l;
	l.find_ledge( &grabber );

	CHECK( l.found_ledge() == true );
}
