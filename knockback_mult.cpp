#include "knockback_mult.h"

knockback_mult::knockback_mult()
	:attackable(),
	 _mult(1)
{
}

knockback_mult::~knockback_mult()
{
}

void knockback_mult::receive_attack( const attack& att )
{
	_mult += float(att.damage()) / 100;
}

void knockback_mult::set_knockback_mult( float mult )
{
	_mult = mult;
}

float knockback_mult::get_knockback_mult() const
{
	return _mult;
}
