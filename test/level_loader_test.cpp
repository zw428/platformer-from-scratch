#include "catch.h"
#include "../level_loader.h"
#include "../manager.h"
#include "../chunk_prop.h"

TEST_CASE( "process_*_str loads into the manager", "[level_loader]" )
{
	manager::instance()->init( true );

	SECTION( "texture" )
	{
		level_loader l;
		l.process_texture_str( "test test.png" );

		CHECK( manager::instance()->textures("test").tex != 0 );
	}

	SECTION( "sound" )
	{
		level_loader l;
		l.process_sound_str( "test test.ogg" );

		CHECK( manager::instance()->sounds("test") != 0 );
	}

	SECTION( "character" )
	{
		SECTION( "player" )
		{
			level_loader l;
			manager::instance()->get_map()->init( 500, 500 );

			l.process_character_str( "player 0 0");

			chunk_prop tmp;
			tmp.x = 0;
			tmp.y = 0;

			CHECK( manager::instance()->get_map()->objects_at( tmp ).size() == 1 );
		}

		SECTION( "npc" )
		{
			level_loader l;
			manager::instance()->get_map()->init( 500, 500 );

			l.process_character_str( "npc 0 0");

			chunk_prop tmp;
			tmp.x = 0;
			tmp.y = 0;

			CHECK( manager::instance()->get_map()->objects_at( tmp ).size() == 1 );
		}
	}

	SECTION( "block" )
	{
			level_loader l;
			manager::instance()->get_map()->init( 500, 500 );

			l.process_texture_str( "test test.png" );
			l.process_block_str( "test 0 0 16 16");

			chunk_prop tmp;
			tmp.x = 0;
			tmp.y = 0;

			CHECK( manager::instance()->get_map()->objects_at( tmp ).size() == 1 );
	}

	SECTION( "font" )
	{
		level_loader l;
		l.process_font_str( "test boo-city.ttf" );

		CHECK( manager::instance()->fonts("test") != 0 );
	}

	SECTION( "map" )
	{
		level_loader l;

		l.process_map_str( "2048 2048" );

		CHECK( manager::instance()->get_map()->x_size() == 2048 );
		CHECK( manager::instance()->get_map()->y_size() == 2048 );
	}

	SECTION( "camera" )
	{
		level_loader l;

		l.process_camera_str( "100 101 102 103" );

		CHECK( manager::instance()->camera_rect().x == 100 );
		CHECK( manager::instance()->camera_rect().y == 101 );
		CHECK( manager::instance()->camera_rect().w == 102 );
		CHECK( manager::instance()->camera_rect().h == 103 );
	}

	SECTION( "trigger" )
	{
		level_loader l;
		manager::instance()->get_map()->init( 500, 500 );

		SECTION( "teleporter" )
		{
			CHECK( l.process_trigger_str( "teleporter 0 0 100 100 200 200" ) == true );
		}

		SECTION( "death" )
		{
			CHECK( l.process_trigger_str( "death 0 0 100 100" ) == true );
		}

		SECTION( "fail" )
		{
			CHECK( l.process_trigger_str( "aaaa 1 1 1 1" ) == false );
		}
	}

	manager::destroy();
}
