#ifndef ANIM_HANDLER_H
#define ANIM_HANDLER_H

#include "anim.h"

class anim_handler
{
public:
	anim_handler();
	void think( bool on_ground, bool facing_left, bool moving, bool disabled );
	void draw( const box* ref );
	anim* current_anim();

	void set_running_anim( anim a );
	void set_idle_anim( anim a );
	void set_jumping_anim( anim a );
	void set_disabled_anim( anim a );

	unsigned short origin() const;
	void origin( unsigned short origin );
private:
	anim _running_anim;
	anim _idle_anim;
	anim _jumping_anim;
	anim _disabled_anim;

	anim* _current_anim;

	unsigned short _origin;
	bool _flipped;
};

#endif
