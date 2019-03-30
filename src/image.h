#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include "box.h"
#include "texture_store.h"

class image : public box
{
public:
	image();

	void draw();
	void texture( texture_store tex_store );
	texture_store tex_store() const;

	void flip_h( bool flipped );
	bool flip_h() const;

	bool tiled() const;
	void tiled( bool tiled );
	bool hidden() const;
	void hide();
	void show();
private:
	texture_store _tex_store;

	void draw_stretched();
	void draw_tiled();

	bool _flip_h;
	bool _tiled;
	bool _hidden;
};

#endif
