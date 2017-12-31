#ifndef NPC_H
#define NPC_H

#include "attackable.h"
#include "disabled.h"
#include "friction.h"
#include "vel_accel.h"
#include "gravity_affected.h"
#include "image.h"

class npc : public attackable
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

