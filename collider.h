#ifndef COLLIDER_H
#define COLLIDER_H

#include "movable.h"
#include "box.h"
#include <vector>

class object;

class collider : public movable, public box
{
public:
	collider();
	collider( object* obj );
	bool colliding(unsigned short dir);
	bool move_phys( short x_add, short y_add );

	void handle_speeds();

	void set_collision_object( object* self );
	object* collision_object();
private:
	object* _collision_obj;
	std::vector<object*> _adjacents;

	void get_adjacents( bool chain );
};

#endif
