#pragma once

#ifndef CREATURE_H
#define CREATURE_H

#include <string>

#include "attackable.h"
#include "mover.h"
#include "ledge_grabber.h"
#include "jumper.h"
#include "gravity_affected.h"
#include "friction.h"
#include "anim_handler.h"

class creature : public attackable
{
public:
	creature();
	~creature();
	virtual bool think_more();
	bool up_pressed;
	bool down_pressed;
	bool left_pressed;
	bool right_pressed;

	bool facing_left() const;
	bool crouching() const;
	bool on_ground() const;
	bool colliding_left() const;
	bool colliding_right() const;

	unsigned short crouch_height() const;
	void crouch_height(unsigned short height);

	unsigned short attack_dir() const;

	void load_consts_from_file(std::string path);

	anim_handler anims;
	mover m;
	jumper jump_handler;
	friction f;
private:
	ledge_grabber _lg;
	gravity_affected _ga;
	bool _facing_left;
	bool _on_ground;
	bool _colliding_left;
	bool _colliding_right;

	unsigned short _crouch_height;
	unsigned short _orig_height;
	bool _was_crouching;
};

#endif
