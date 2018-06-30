#pragma once

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

	bool up_was_pressed() const;
	bool down_was_pressed() const;
	bool left_was_pressed() const;
	bool right_was_pressed() const;
private:
	bool _up_was_pressed;
	bool _down_was_pressed;
	bool _left_was_pressed;
	bool _right_was_pressed;

	bool _can_change_attack_dir;
};

#endif
