#include "catch.hpp"
#include "../camera.h"

TEST_CASE( "camera constructor initializes", "[camera]" )
{
	camera c;

	CHECK( c.camera_rect().x == 0 );
	CHECK( c.camera_rect().y == 0 );
	CHECK( c.camera_rect().w == 0 );
	CHECK( c.camera_rect().h == 0 );
}

TEST_CASE( "camera can have dimensions set/get", "[camera]" )
{
	SECTION( "set_camera(rect)" )
	{
		camera c;
		SDL_Rect r;
		r.x = 5;
		r.y = 6;
		r.w = 7;
		r.h = 8;

		c.set_camera( r );

		CHECK( c.camera_rect().x == 5 );
		CHECK( c.camera_rect().y == 6 );
		CHECK( c.camera_rect().w == 7 );
		CHECK( c.camera_rect().h == 8 );
	}

	SECTION( "set_camera(x,y)" )
	{
		camera c;
		c.set_camera( 5, 6 );
		
		CHECK( c.camera_rect().x == 5 );
		CHECK( c.camera_rect().y == 6 );
	}

	SECTION( "resize_camera(w,h)" )
	{
		camera c;
		c.resize_camera( 5, 6 );

		CHECK( c.camera_rect().w == 5 );
		CHECK( c.camera_rect().h == 6 );
	}

}

TEST_CASE( "camera can give relative coordinates", "[camera]" )
{
	camera c;

	int camera_x = 100;
	int camera_y = 100;

	c.set_camera( camera_x, camera_y );

	int test_x = 500;
	int test_y = 600;

	CHECK( c.camera_coords( test_x, test_y ).x == test_x - camera_x );
	CHECK( c.camera_coords( test_x, test_y ).y == test_y - camera_y );
}
