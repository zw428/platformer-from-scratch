#include "catch.hpp"
#include "../death_box.h"
#include "../death.h"
#include "../object.h"

class death_box_tmp : public death, public object
{
public:
	bool dead = false;
	bool think() { return false; };
	bool on_death() { dead = true; return true; };
};

TEST_CASE( "death_box calls on_death() on object", "[attack_box]" )
{
	death_box_tmp t;

	death_box death_b;

	death_b.action(&t);

	CHECK( t.dead == true );
}
