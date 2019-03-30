#include <catch2/catch.hpp>
#include "keys.h"
#include <SDL2/SDL.h>

TEST_CASE( "keys::think picks up keys/mouse", "[keys]" )
{
	keys::reset();

	SECTION( "mouse coords" )
	{
		SDL_Event e;
		e.type = SDL_MOUSEMOTION;
		e.motion.x = 5;
		e.motion.y = 6;

		keys::instance()->think( &e );

		CHECK( keys::instance()->mouse_x() == 5 );
		CHECK( keys::instance()->mouse_y() == 6 );
	}

	SECTION( "mouse clicks" )
	{
		SDL_Event e;

		e.type = SDL_MOUSEBUTTONUP;

		e.button.button = SDL_BUTTON_LEFT;
		keys::instance()->think(&e);
		CHECK( keys::instance()->mouse_pressed(0) == false );

		e.button.button = SDL_BUTTON_RIGHT;
		keys::instance()->think(&e);
		CHECK( keys::instance()->mouse_pressed(1) == false );

		e.type = SDL_MOUSEBUTTONDOWN;

		e.button.button = SDL_BUTTON_LEFT;
		keys::instance()->think(&e);
		CHECK( keys::instance()->mouse_pressed(0) == true );

		e.button.button = SDL_BUTTON_RIGHT;
		keys::instance()->think(&e);
		CHECK( keys::instance()->mouse_pressed(1) == true );
	}

	SECTION( "buttons" )
	{
		CHECK( keys::instance()->key_pressed( SDLK_SPACE ) == false );

		SDL_Event e;

		e.key.keysym.sym = SDLK_SPACE;

		e.type = SDL_KEYDOWN;
		keys::instance()->think(&e);
		CHECK( keys::instance()->key_pressed( SDLK_SPACE ) == true );

		e.type = SDL_KEYUP;
		keys::instance()->think(&e);
		CHECK( keys::instance()->key_pressed( SDLK_SPACE ) == false );
	}
}
