#ifndef ATTACK_BOX_H
#define ATTACK_BOX_H

#include "trigger.h"
#include "attack.h"

class object;

class attack_box : public trigger
{
public:
	attack_box();
	~attack_box();

	void set_attack( attack att );

	bool action( box_object* bo );
private:
	attack _attack;
};

#endif
