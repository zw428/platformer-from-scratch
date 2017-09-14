#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>

class object;

class collider
{
public:
	collider();
	bool colliding(object* obj, unsigned short dir);
	bool move_phys( object* obj, short x_add, short y_add );

	void handle_speeds( object* obj );
private:
	std::vector<object*> _adjacents;

	void get_adjacents( object* obj, bool chain );
};

#endif
