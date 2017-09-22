#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include "attack.h"

class object;
class box;

void knockback( object* obj, box* source, const attack& att );

#endif
