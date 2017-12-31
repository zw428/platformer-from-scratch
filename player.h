#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"

class player : public creature
{
public:
	player();
	~player();
	bool think();
private:
	anim _idle;
	anim _running;
	anim _jumping;
	anim _hanging;
	anim _punching;
};

#endif
