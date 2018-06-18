#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include "attack.h"
#include "box.h"

class attackable;

//hit angle = where hit went according to attacker; like a bullet going right's hit angle would typically be 0
//set hit angle assuming the attack is facing right
void knockback( attackable* atbl, double hit_angle, const attack& att );

#endif
