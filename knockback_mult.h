#ifndef KNOCKBACK_MULT_H
#define KNOCKBACK_MULT_H

#include "attackable.h"
#include "attack.h"

class knockback_mult : public attackable
{
public:
	knockback_mult();
	~knockback_mult();
	void receive_attack( const attack& att );
	void set_knockback_mult( float mult );
	float get_knockback_mult() const;
private:
	float _mult;
};

#endif
