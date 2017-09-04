#ifndef ATTACK_H
#define ATTACK_H

#include "sound_player.h"

class alive;

class attack : public sound_player
{
public:
	attack();

	void damage( unsigned short damage );
	unsigned short damage() const;

	void knockback( unsigned short knockback );
	unsigned short knockback() const;

	alive* owner();
	void owner( alive* own );

	void perform( alive* al );
private:
	void reset_delay();

	unsigned short _damage;
	unsigned short _knockback;

	alive* _owner;
};

#endif
