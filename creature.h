#ifndef CREATURE_H
#define CREATURE_H

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
	virtual bool think();
	bool up_pressed;
	bool down_pressed;
	bool left_pressed;
	bool right_pressed;

	anim_handler anims;
	mover m;
	jumper jump_handler;
private:
	ledge_grabber _lg;
	gravity_affected _ga;
	friction _f;
};

#endif
