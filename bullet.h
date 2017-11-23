#ifndef BULLET_H
#define BULLET_H

#include "object.h"
#include "image.h"
#include "vel_accel.h"
#include "attack.h"
#include "texture_store.h"

class bullet : public object, public image, public vel_accel, public attack
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
