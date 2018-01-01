#ifndef DELAYED_ATTACK_H
#define DELAYED_ATTACK_H

#include "delayed_action.h"
#include "attack.h"
#include "anim.h"

class delayed_attack
{
public:
	delayed_attack();
	virtual ~delayed_attack();
	virtual void perform() = 0;
	attack att;
	delayed_action action;
	anim animation;
	void think( bool start_attack );
};

#endif
