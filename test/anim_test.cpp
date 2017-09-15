#include "catch.h"
#include "../anim.h"

TEST_CASE( "anim constructor initializes stuff", "[anim]" )
{
	anim a;

	CHECK( a.clip_offset() == 0 );
	CHECK( a.clip_width() == 0 );
	CHECK( a.frame_dur() == 5 );
}

TEST_CASE( "anim setters/getters work", "[anim]" )
{
	anim a;

	a.clip_offset(12);
	a.clip_width(13);
	a.frame_dur(14);

	CHECK(a.clip_offset() == 12);
	CHECK(a.clip_width() == 13);
	CHECK(a.frame_dur() == 14);
}

TEST_CASE( "anim caps frame_dur to 1", "[anim]" )
{
	anim a;

	a.frame_dur(0);

	CHECK( a.frame_dur() == 1 );
}

TEST_CASE( "anim draw continues and loops the clip offset", "[anim]" )
{
	manager::instance()->init(true);

	manager::instance()->add_texture( "sheet.png", "sheet" );
	anim a;
	a.texture( manager::instance()->textures("sheet") );
	CHECK(a.tex_store().orig_w == 500 );

	a.clip_width(100);
	a.frame_dur(5);

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
