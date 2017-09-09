#include "catch.hpp"
#include "../map.h"
#include "../object.h"

class map_tmp : public object
{
public:
	bool think() { return false; };
};

class map_tmp2 : public trigger
{
public:
	bool action( object* obj ) { return false; };
};

TEST_CASE( "map constructor initializes stuff", "[map]" )
{
	SECTION ( "map()" )
	{
		map m;

		CHECK( m.x_size() == 0 );
		CHECK( m.y_size() == 0 );
	}

	SECTION( "map( x_size, y_size )" )
	{
		map m(500,500);

		CHECK( m.x_size() == 256 );
		CHECK( m.y_size() == 256 );
	}
}

TEST_CASE( "map::init() rounds to nearest multiple of chunk size", "[map]" )
{
	map m;

	m.init(1000,1000);

	CHECK( m.x_size() == 768 );
	CHECK( m.y_size() == 768 );
}

TEST_CASE( "map::add_object adds objects", "[map]" )
{
	map m;
	m.init(512,512);

	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);

	m.add_object(mt);

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.objects_at( cp ).size() == 1 );
}

TEST_CASE( "map::add_trigger adds triggers", "[map]" )
{
	map m;

	m.init(1000,1000);

	map_tmp2* mt = new map_tmp2;

	mt->x(0);
	mt->y(0);

	CHECK( m.add_trigger(mt) == true );
}

TEST_CASE( "map setters and getters work", "[map]" )
{
	map m;

	m.init(512,512);

	CHECK( m.x_size() == 512 );
	CHECK( m.y_size() == 512 );

	CHECK( m.chunk_x_size() == 2 );
	CHECK( m.chunk_y_size() == 2 );
}

TEST_CASE( "map::empty empties everything", "[map]" )
{
	map m;
	m.init(512,512);

	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);

	m.add_object(mt);

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.objects_at( cp ).size() == 1 );

	m.empty();
	
	CHECK( m.objects_at( cp ).size() == 0 );
}

TEST_CASE( "map::objects_at gives all objects in a chunk", "[map]" )
{
	map m;
	m.init(512,512);
	
	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);
	
	map_tmp* mt2 = new map_tmp;
	mt2->x(0);
	mt2->y(0);

	m.add_object( mt );
	m.add_object( mt2 );
	
	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.objects_at( cp ).size() == 2 );
}

TEST_CASE( "map::objects_at doesn't give objects from different chunks", "[map]" )
{
	map m;
	m.init(1024,1024);
	
	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);
	
	map_tmp* mt2 = new map_tmp;
	mt2->x(300);
	mt2->y(300);

	m.add_object( mt );
	m.add_object( mt2 );
	
	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;
	CHECK( m.objects_at( cp ).size() == 1 );

	cp.x = 1;
	cp.y = 1;
	CHECK( m.objects_at( cp ).size() == 1 );
	
	cp.x = 2;
	cp.y = 2;
	CHECK( m.objects_at( cp ).size() == 0 );
}

TEST_CASE( "map::objects_at ignores the ignore", "[map]" )
{
	map m;
	m.init(1024,1024);
	
	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);
	
	m.add_object( mt );
	
	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;
	
	CHECK( m.objects_at( cp, mt ).size() == 0 );
}

TEST_CASE( "map::objects_considered gets objects in and around chunk", "[map]" )
{
	map m;
	m.init(1024,1024);
	
	map_tmp* mt = new map_tmp;
	mt->x(0);
	mt->y(0);
	
	map_tmp* mt2 = new map_tmp;
	mt2->x(300);
	mt2->y(300);

	m.add_object( mt );
	m.add_object( mt2 );
	
	CHECK( m.objects_considered( mt ).size() == 1 );
	CHECK( m.objects_considered( mt )[0] == mt2 );
}
