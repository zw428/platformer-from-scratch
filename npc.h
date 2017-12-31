#ifndef NPC_H
#define NPC_H

#include "knockback_mult.h"
#include "disabled.h"
#include "friction.h"
#include "vel_accel.h"
#include "gravity_affected.h"
#include "image.h"

class npc : public knockback_mult
{
public:
	npc();
	~npc();
	bool think();
private:
	friction _f;
	gravity_affected _ga;
	image _img;
};

#endif

