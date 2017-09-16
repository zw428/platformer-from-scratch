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

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class player : public alive, public object, public jumper, public gravity_affected, public mover, public friction, public vel_accel
{
public:
	player();
	~player();
	bool think();
	void start_attack();
private:
	unsigned short _attack_counter;
	unsigned short _attack_delay;

	anim _anm;
};

#endif
