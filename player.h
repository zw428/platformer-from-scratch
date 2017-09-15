#ifndef PLAYER_H
#define PLAYER_H

#include "alive.h"
#include "gravity_affected.h"
#include "anim.h"
#include "object.h"
#include "jumper.h"
#include "collider.h"
#include "mover.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class player : public alive, public object, public jumper, public gravity_affected, public mover
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
