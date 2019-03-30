#pragma once

#ifndef DELAYED_ATTACK_BULLET_H
#define DELAYED_ATTACK_BULLET_H

#include "delayed_attack.h"
#include "vel_accel.h"

#include <string>

class delayed_attack_bullet : public delayed_attack
{
public:
	delayed_attack_bullet();
	~delayed_attack_bullet();
	void speed(float speed);
	float speed() const;
	void perform();
	void load_data_from_file(std::string path);

	box dimens;
	coords offset;
private:
	float _speed;
};

#endif
