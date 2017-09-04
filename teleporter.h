#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "collider.h"

class teleporter : public collider
{
public:
	teleporter();
	bool teleport( int x, int y );
private:
};

#endif
