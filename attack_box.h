#ifndef ATTACK_BOX_H
#define ATTACK_BOX_H

#include "trigger.h"
#include "attack.h"
#include "image.h"

class attack_box : public trigger, public attack
{
public:
	attack_box();
	~attack_box();

	bool action(object* obj);
private:
	attack _attack;
	object* _owner;
};

#endif
