#ifndef ANIM_HANDLER_H
#define ANIM_HANDLER_H

#include "anim.h"

class anim_handler
{
public:
	anim_handler();
	void think( bool on_ground, bool facing_left, bool moving, bool disabled );
	anim* current_anim() const;

	void set_running_anim( anim a );
	void set_idle_anim( anim a );
	void set_jumping_anim( anim a );
	void set_disabled_anim( anim a );
private:
	anim* _current_anim;

	anim _running_anim;
	anim _idle_anim;
	anim _jumping_anim;
	anim _disabled_anim;
};

#endif
