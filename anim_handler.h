#pragma once

#ifndef ANIM_HANDLER_H
#define ANIM_HANDLER_H

#include "anim.h"
#include "origin.h"

class anim_handler
{
public:
	anim_handler();
	void think( bool on_ground, bool facing_left, bool moving, bool hanging, bool disabled );
	void draw( const box& ref );
	anim* current_anim();

	void set_running_anim( anim a );
	void set_idle_anim( anim a );
	void set_jumping_anim( anim a );
	void set_disabled_anim( anim a );
	void set_hanging_anim( anim a );
	void set_override_anim( anim* a );

	origin the_origin;
private:
	anim _running_anim;
	anim _idle_anim;
	anim _jumping_anim;
	anim _disabled_anim;
	anim _hanging_anim;

	anim* _current_anim;

	bool _override_anim_active;
	unsigned short _origin;
	bool _flipped;
};

#endif
