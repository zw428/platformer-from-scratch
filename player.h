#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "delayed_attack_box.h"

class player : public creature
{
public:
	player();
	~player();
	bool think();
private:
	delayed_attack_box _dab;
	anim _idle;
	anim _running;
	anim _jumping;
	anim _hanging;
	anim _punching;
};

#endif
