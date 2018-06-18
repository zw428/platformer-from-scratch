#ifndef ATTACK_H
#define ATTACK_H

#include "sound_player.h"

class attackable;
class box;

class attack : public sound_player
{
public:
	attack();

	void damage( unsigned short damage );
	unsigned short damage() const;

	void knockback( unsigned short knockback );
	unsigned short knockback() const;

	double hit_angle() const;
	void hit_angle(double ang);

	attackable* owner() const;
	void owner( attackable* own );

	bool perform( attackable* a, double hit_angle );
private:
	unsigned short _damage;
	unsigned short _knockback;

	double _hit_angle;

	attackable* _owner;
};

#endif
