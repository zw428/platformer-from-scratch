#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "delayed_attack_box.h"
#include "delayed_attack_bullet.h"
#include "attack_manager.h"

class player : public creature
{
public:
	player();
	~player();
	bool think_more();
private:
	attack_manager _am;
	anim _idle;
	anim _running;
	anim _jumping;
	anim _hanging;
	anim _punching;
	anim _crouching;
};

#endif
