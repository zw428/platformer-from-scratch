#pragma once

#ifndef NPC_H
#define NPC_H

#include "creature.h"

class npc : public creature
{
public:
	npc();
	~npc();
private:
	anim _blank;
};

#endif
