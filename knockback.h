#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include "attack.h"
#include "box.h"

class attackable;

void knockback( attackable* atbl, box source, const attack& att );

#endif
