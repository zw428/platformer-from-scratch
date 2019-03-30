#include <catch2/catch.hpp>
#include "spawnable.h"

class spawnable_tmp : public spawnable
{
public:
	void on_spawn() { spawned = true; return; };
	bool spawned = false;
};

TEST_CASE( "spawnable knows when it's spawning and triggers the callback", "[spawnable]" )
{
	spawnable_tmp s;

	s.spawn_delay(5);

	CHECK( s.spawning() == false );

	s.spawn();

	CHECK( s.spawning() == true );

	for ( unsigned i=0; i < 5; i++ )
	{
		s.handle_spawning();
	}

	CHECK( s.spawning() == false );
	CHECK( s.spawned == true );
}
