#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "delayed_attack_box.h"
#include "delayed_attack_bullet.h"

class player : public creature
{
public:
	player();
	~player();
	bool think_more();
private:
	delayed_attack_box _dab;
	delayed_attack_bullet _dab2;
	anim _idle;
	anim _running;
	anim _jumping;
	anim _hanging;
	anim _punching;
};

#endif
