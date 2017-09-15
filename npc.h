#ifndef NPC_H
#define NPC_H

#include "knockback_mult.h"
#include "object.h"
#include "death.h"
#include "disabled.h"
#include "gravity_affected.h"
#include "image.h"
#include "collider.h"
#include "friction.h"

class npc : public knockback_mult, public object, public death, public disabled, public friction, public gravity_affected
{
public:
	npc();
	~npc();
	bool think();
	bool on_death();
private:
	image _img;
};

#endif

