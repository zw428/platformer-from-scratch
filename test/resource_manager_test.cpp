#include "catch.hpp"
#include "../resource_manager.h"
#include "../manager.h"

TEST_CASE( "resource manager can add/remove stuff", "[resource_manager]" )
{
	manager::instance()->init(true);

	resource_manager r;

	SECTION( "texture" )
	{
		r.add_texture( "test.png", "test" );

		CHECK( r.textures("test").tex != 0 );
		CHECK( r.textures("test").orig_w == 100 );
		CHECK( r.textures("test").orig_h == 100 );

		r.destroy_textures();

		CHECK( r.textures("test").tex == 0 );
	}

	SECTION( "sound" )
	{
		r.add_sound( "test.ogg", "test" );

		CHECK( r.sounds("test") != 0 );

		r.destroy_sounds();

		CHECK( r.sounds("test") == 0 );
	}

	SECTION( "font" )
	{
		r.add_font( "boo-city.ttf", "test" );

		CHECK( r.fonts("test") != 0 );

		r.destroy_fonts();

		CHECK( r.fonts("test") == 0 );
	}

	manager::destroy();
}
