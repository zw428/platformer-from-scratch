#include "catch.hpp"
#include "../jumper.h"
#include "../object.h"
#include "../manager.h"
#include "../block.h"

class jumper_tmp : public object
{
public:
	bool think() { return false; };
};

TEST_CASE( "jumper constructor initializes stuff", "[jumper]" )
{
	jumper j;

	CHECK( j.jump_vel_1() == 9 );
	CHECK( j.jump_vel_2() == 8 );
	CHECK( j.times_jumped() == 0 );
}

TEST_CASE( "jumper setters/getters work", "[jumper]" )
{
	jumper j;

	j.jump_vel_1(10);
	j.jump_vel_2(11);

	CHECK( j.jump_vel_1() == 10 );
	CHECK( j.jump_vel_2() == 11 );
}

TEST_CASE( "jumper correctly handles jumping from the ground", "[jumper]" )
{
	manager::instance()->get_map()->init(512,512);

	block* b = new block;

	b->x(0);
	b->y(100);
	b->w(200);
	b->h(50);

	manager::instance()->get_map()->add_object(b);

	jumper_tmp* obj = new jumper_tmp;

	obj->x(0);
	obj->y(79);
	obj->w(20);
	obj->h(20);

	manager::instance()->get_map()->add_object(obj);

	obj->move_phys(0,1); //because move_phys is what calls get_adjacents()
	CHECK( obj->times_jumped() == 0 );

	obj->handle_jumping(false);
	obj->handle_jumping(true);
	obj->handle_speeds();

	CHECK( obj->times_jumped() == 1 );

	obj->handle_jumping(true);
	obj->handle_speeds();

	CHECK( obj->times_jumped() == 1 );

	obj->handle_jumping(false);
	obj->handle_jumping(true);
	obj->handle_speeds();

	CHECK( obj->times_jumped() == 2 );

	obj->handle_jumping(false);
	obj->handle_jumping(true);
	obj->handle_speeds();

	CHECK( obj->times_jumped() == 2 );

	manager::destroy();
}

TEST_CASE( "jumper correctly handles jumping after falling", "[jumper]" )
{
	manager::instance()->get_map()->init(512,512);

	block* b = new block;

	b->x(0);
	b->y(100);
	b->w(200);
	b->h(50);

	manager::instance()->get_map()->add_object(b);

	jumper_tmp* obj = new jumper_tmp;

	obj->x(199);
	obj->y(80);
	obj->w(20);
	obj->h(20);

	manager::instance()->get_map()->add_object(obj);

	obj->move_phys(30,0); //because move_phys is what calls get_adjacents()
	obj->handle_speeds();
	obj->handle_jumping(false);
	CHECK( obj->times_jumped() == 1 );

	obj->handle_jumping(true);
	obj->handle_speeds();
	CHECK( obj->times_jumped() == 2 );

	manager::destroy();
}
