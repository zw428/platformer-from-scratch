#include "catch.h"
#include "../manager.h"
#include "../anim.h"

TEST_CASE( "anim constructor initializes stuff", "[anim]" )
{
	anim a;

	CHECK( a.clip_offset() == 0 );
	CHECK( a.clip_width() == 0 );
}

TEST_CASE( "anim acts as image when no frames are added", "[anim]" )
{
	anim a;

	CHECK( a.num_frames() == 1 );
}

TEST_CASE( "anim setters/getters work", "[anim]" )
{
	anim a;

	a.clip_offset(12);
	a.clip_width(13);

	CHECK(a.clip_offset() == 12);
	CHECK(a.clip_width() == 13);
}

TEST_CASE( "anim draw continues and loops the clip offset", "[anim]" )
{
	manager::instance()->init(true);

	manager::instance()->add_texture( "sheet.png", "sheet" );
	anim a;
	a.texture( manager::instance()->textures("sheet") );
	CHECK(a.tex_store().orig_w == 500 );

	a.clip_width(100);

	for ( unsigned i=0; i < 5; i++ )
	{
		a.add_frame_dur(5);
	}

	for ( unsigned i=0; i < 5; i++ )
	{
		a.draw();
	}

	CHECK( a.clip_offset() == 100 );

	for ( unsigned i=0; i < 15; i++ )
	{
		a.draw();
	}

	CHECK( a.clip_offset() == 400 );

	for ( unsigned i=0; i < 5; i++ )
	{
		a.draw();
	}

	CHECK( a.clip_offset() == 0 );

	manager::destroy();
}

TEST_CASE( "anim draw throws an exception if not enough frame_durs", "[anim]" )
{
	manager::instance()->init(true);

	manager::instance()->add_texture( "sheet.png", "sheet" );
	anim a;
	a.texture( manager::instance()->textures("sheet") );

	a.clip_width(100);

	CHECK_THROWS(a.draw());
	manager::destroy();
}
