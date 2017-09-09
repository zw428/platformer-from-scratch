#ifndef NPC_H
#define NPC_H

#include "knockback_mult.h"
#include "object.h"
#include "death.h"
#include "disabled.h"
#include "image.h"

class npc : public knockback_mult, public object, public death, public disabled
{
public:
	npc();
	~npc();
	bool think();
	bool on_death();
	void dest( unsigned short x, unsigned short y );
private:
	unsigned short _x_dest;
	unsigned short _y_dest;

	image _img;
};

#endif

