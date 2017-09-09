#include "catch.hpp"
#include "../shared_texture.h"

TEST_CASE( "shared_texture keeps track of how many there are", "[shared_texture]" )
{
	shared_texture t;
	CHECK( t.count() == 1 );

	shared_texture t2 = t;
	
	CHECK( t2.count() == 2 );
	CHECK( t.count() == 2 );

	shared_texture t3(t);
	
	CHECK( t3.count() == 3 );
	CHECK( t2.count() == 3 );
	CHECK( t.count() == 3 );

	if ( true ) //test scope
	{
		shared_texture t4(t);

		CHECK( t4.count() == 4 );
		CHECK( t3.count() == 4 );
		CHECK( t2.count() == 4 );
		CHECK( t.count() == 4 );
	}

	CHECK( t3.count() == 3 );
	CHECK( t2.count() == 3 );
	CHECK( t.count() == 3 );
}

TEST_CASE( "shared_texture setters/getters work", "[shared_texture]" )
{
	shared_texture t;

	t.tex(0);

	CHECK( t.tex() == 0 );
}
