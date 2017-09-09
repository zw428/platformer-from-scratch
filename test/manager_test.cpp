#include "catch.hpp"
#include "../manager.h"

TEST_CASE( "manager setters/getters work", "[manager]" )
{
	manager::instance()->data_path( "asdf" );

	CHECK( manager::instance()->data_path() == "asdf" );
}
