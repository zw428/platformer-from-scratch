#include "catch.h"
#include "../map.h"
#include "../object.h"
#include "../trigger.h"

class map_tmp : public object {
public:
	bool think() { return false; };
};

class map_tmp2 : public trigger
{
public:
	bool action( box_object* bo ) { return false; };
};

TEST_CASE( "map( x_size, y_size ) rounds to nearest power of 2", "[map]" )
{
	map m(500,500);

	CHECK( m.x_size() == 256 );
	CHECK( m.y_size() == 256 );
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

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	m.add_object(mt);

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.box_objects_in_chunk( cp ).size() == 1 );
}

TEST_CASE( "map::object_count works correctly", "[map]" )
{
	map m;
	m.init(512,512);

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	m.add_object(mt);

	CHECK( m.object_count() == 1 );

	m.empty();
	
	CHECK( m.object_count() == 0 );
}

TEST_CASE( "map::trigger_count works correctly", "[map]" )
{
	map m;

	m.init(1000,1000);

	map_tmp2* mt = new map_tmp2;

	mt->dimens.x(0);
	mt->dimens.y(0);

	m.add_object(mt);

	CHECK( m.trigger_count() == 1 );
	
	m.empty();
	
	CHECK( m.trigger_count() == 0 );
}

TEST_CASE( "map::add_object adds triggers", "[map]" )
{
	map m;

	m.init(1000,1000);

	map_tmp2* mt = new map_tmp2;

	mt->dimens.x(0);
	mt->dimens.y(0);

	CHECK( m.add_object(mt) == true );
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

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	m.add_object(mt);

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.box_objects_in_chunk( cp ).size() == 1 );

	m.empty();

	CHECK( m.box_objects_in_chunk( cp ).size() == 0 );
}

TEST_CASE( "map::box_objects_in_chunk gives all objects in a chunk", "[map]" )
{
	map m;
	m.init(512,512);

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	box_object* mt2 = new box_object;
	mt2->dimens.x(0);
	mt2->dimens.y(0);

	m.add_object( mt );
	m.add_object( mt2 );

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.box_objects_in_chunk( cp ).size() == 2 );
}

TEST_CASE( "map::box_objects_in_chunk doesn't give objects from different chunks", "[map]" )
{
	map m;
	m.init(1024,1024);

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	box_object* mt2 = new box_object;
	mt2->dimens.x(300);
	mt2->dimens.y(300);

	m.add_object( mt );
	m.add_object( mt2 );

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;
	CHECK( m.box_objects_in_chunk( cp ).size() == 1 );

	cp.x = 1;
	cp.y = 1;
	CHECK( m.box_objects_in_chunk( cp ).size() == 1 );

	cp.x = 2;
	cp.y = 2;
	CHECK( m.box_objects_in_chunk( cp ).size() == 0 );
}

TEST_CASE( "map::box_objects_in_chunk ignores the ignore", "[map]" )
{
	map m;
	m.init(1024,1024);

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	m.add_object( mt );

	chunk_prop cp;
	cp.x = 0;
	cp.y = 0;

	CHECK( m.box_objects_in_chunk( cp, mt ).size() == 0 );
}

TEST_CASE( "map::box_objects_in_box gives objects in the given box", "[map]" )
{
	map m;
	m.init(1024,1024);

	box_object* mt = new box_object;
	mt->dimens.x(400);
	mt->dimens.y(400);

	m.add_object( mt );

	box b;

	b.x(380);
	b.y(380);

	b.w(30);
	b.h(30);

	CHECK( m.box_objects_in_box(b).size() == 1 );
}

TEST_CASE( "map::box_objects_in_box can span multiple chunks", "[map]" )
{
	map m;
	m.init(2048,2048);

	box_object* mt = new box_object;
	mt->dimens.x(100);
	mt->dimens.y(100);

	m.add_object( mt );

	box_object* mt2 = new box_object;
	mt->dimens.x(1500);
	mt->dimens.y(1500);

	m.add_object( mt2 );

	box b;

	b.x(10);
	b.y(10);

	b.w(1600);
	b.h(1600);

	CHECK(1500 > CHUNK_SIZE);

	CHECK( m.box_objects_in_box(b).size() == 2 );
}

TEST_CASE( "map::box_objects_considered gets objects in and around chunk", "[map]" )
{
	map m;
	m.init(1024,1024);

	box_object* mt = new box_object;
	mt->dimens.x(0);
	mt->dimens.y(0);

	box_object* mt2 = new box_object;
	mt2->dimens.x(300);
	mt2->dimens.y(300);

	m.add_object( mt );
	m.add_object( mt2 );

	CHECK( m.box_objects_considered( mt ).size() == 1 );
	CHECK( m.box_objects_considered( mt )[0] == mt2 );
}
