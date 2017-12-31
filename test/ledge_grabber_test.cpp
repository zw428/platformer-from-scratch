#include "catch.h"
#include "../ledge_grabber.h"
#include "../manager.h"
#include "../block.h"
#include "../object.h"
#include "../vel_accel.h"

TEST_CASE("ledge_grabber gives correct distances to ledge", "[ledge_grabber]")
{
	block* ledge = new block;
	ledge->dimens.x(200);
	ledge->dimens.y(200);
	ledge->dimens.w(40);
	ledge->dimens.h(20);

	manager::instance()->the_map.empty();
	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(ledge);

	box_object grabber;
	grabber.dimens.x( 245 );
	grabber.dimens.y( 190 );
	grabber.dimens.w( 20 );
	grabber.dimens.h( 20 );
	grabber.speeds.v_speed( 5 );

	ledge_grabber l;
	l.find_ledge( grabber.speeds, grabber.dimens, false );

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
			grabber.dimens.x( 175 );
			l.find_ledge( grabber.speeds, grabber.dimens, false );
			CHECK( l.h_dist_to_ledge() == 5 );
		}
	}
}

TEST_CASE("ledge_grabber finds ledge", "[ledge_grabber]")
{
	block* ledge = new block;
	ledge->dimens.x(200);
	ledge->dimens.y(200);
	ledge->dimens.w(40);
	ledge->dimens.h(20);

	manager::instance()->the_map.empty();
	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(ledge);

	box_object grabber;
	grabber.dimens.x( 245 );
	grabber.dimens.y( 190 );
	grabber.dimens.w( 20 );
	grabber.dimens.h( 20 );
	grabber.speeds.v_speed( 5 );

	ledge_grabber l;
	l.find_ledge( grabber.speeds, grabber.dimens, false );

	CHECK( l.found_ledge() == true );
}
