#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include "attack.h"
#include "box.h"

class box_object;

void knockback( box_object* mbo, box source, const attack& att );

#endif
