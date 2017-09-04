#ifndef KNOCKBACK_MULT_H
#define KNOCKBACK_MULT_H

#include "alive.h"
#include "attack.h"

class knockback_mult : public alive
{
public:
	knockback_mult();
	void receive_attack( const attack& att );
	void set_knockback_mult( float mult );
	float get_knockback_mult();
private:
	float _mult;
};

#endif
