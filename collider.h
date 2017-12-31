#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>
class vel_accel;

class box_object;

bool colliding(box_object* bo, unsigned short dir);
std::vector<box_object*> move( box_object* bo, short x_add, short y_add );
bool move_phys( box_object* bo, short x_add, short y_add );
void handle_speeds( vel_accel& va, box_object* bo );
std::vector<box_object*> get_adjacents( box_object* bo );

#endif
