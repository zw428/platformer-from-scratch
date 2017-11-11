#ifndef PLAYER_H
#define PLAYER_H

#include "alive.h"
#include "object.h"
#include "jumper.h"
#include "gravity_affected.h"
#include "mover.h"
#include "friction.h"
#include "vel_accel.h"
#include "anim.h"
#include "ledge_grabber.h"
#include "delayed_action.h"
#include "anim_handler.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class player : public alive, public object, public jumper, public gravity_affected, public mover, public friction, public vel_accel, public ledge_grabber
{
public:
	player();
	~player();
	bool think();
	void start_attack();
private:
	unsigned short _attack_counter;
	unsigned short _attack_delay;

	delayed_action _attack1;

	anim _idle;
	anim _running;
	anim _jumping;
	anim _hanging;
	anim _punching;

	anim_handler _am;
};

#endif
