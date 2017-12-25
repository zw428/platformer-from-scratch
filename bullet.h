#ifndef BULLET_H
#define BULLET_H

#include "attack_box.h"
#include "anim.h"

class bullet : public attack_box, public anim
{
public:
	bullet();
	void reverse();
	bool think();
private:
	unsigned short _speed;
	bool _reversed;
	float _theta;
};

#endif
