#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>

class object;

bool colliding(object* obj, unsigned short dir);
bool move_phys( object* obj, short x_add, short y_add );
void handle_speeds( object* obj );
std::vector<object*> get_adjacents( object* obj );

#endif
