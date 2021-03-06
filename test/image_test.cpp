#include <catch2/catch.hpp>
#include "image.h"

TEST_CASE( "image setters and getters work", "[image]" )
{
	image i;
	texture_store t;
	t.tex = 0;
	t.orig_w = 5;
	t.orig_h = 6;

	i.texture( t );
	i.flip_h( true );
	i.tiled( true );

	CHECK( i.tex_store().tex == 0 );
	CHECK( i.tex_store().orig_w == 5 );
	CHECK( i.tex_store().orig_h == 6 );
	CHECK( i.flip_h() == true );
	CHECK( i.tiled() == true );
}
