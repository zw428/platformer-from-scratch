#ifndef TELEPORT_BOX_H
#define TELEPORT_BOX_H

#include "trigger.h"

class teleport_box : public trigger
{
public:
	teleport_box();
	~teleport_box();

	void set_dest( int x, int y );

	bool action(object* obj);
private:
	int _x_dest;
	int _y_dest;
};

#endif
