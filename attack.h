#ifndef ATTACK_H
#define ATTACK_H

#include "sound_player.h"

class attackable;

class attack : public sound_player
{
public:
	attack();

	void damage( unsigned short damage );
	unsigned short damage() const;

	void knockback( unsigned short knockback );
	unsigned short knockback() const;

	attackable* owner() const;
	void owner( attackable* own );

	void perform( attackable* a );
private:
	unsigned short _damage;
	unsigned short _knockback;

	attackable* _owner;
};

#endif
