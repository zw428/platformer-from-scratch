#ifndef NPC_H
#define NPC_H


#include <SDL2/SDL.h>
#include <queue>
#include <memory>

#include "knockback_mult.h"
#include "object.h"
#include "image.h"
#include "mover.h"

class npc : public knockback_mult, public object
{
public:
	npc();
	~npc();
	bool think();
	void dest( unsigned short x, unsigned short y );
	bool can_move();
private:
	bool _can_move;
	unsigned short _x_dest;
	unsigned short _y_dest;

	image _img;
};

#endif

