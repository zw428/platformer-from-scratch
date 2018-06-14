#ifndef DELAYED_ATTACK_BULLET_H
#define DELAYED_ATTACK_BULLET_H

#include "delayed_attack.h"
#include "vel_accel.h"

class delayed_attack_bullet : public delayed_attack
{
public:
	delayed_attack_bullet();
	~delayed_attack_bullet();
	void perform();
};

#endif
