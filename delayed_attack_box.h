#pragma once

#ifndef DELAYED_ATTACK_BOX_H
#define DELAYED_ATTACK_BOX_H

#include "delayed_attack.h"

class delayed_attack_box : public delayed_attack
{
public:
	delayed_attack_box();
	~delayed_attack_box();
	void perform();
	box dimens;
	coords offset;
	bool add_as_child;
};

#endif
