#ifndef GRAVITY_AFFECTED_H
#define GRAVITY_AFFECTED_H

#include "collider.h"

class gravity_affected : public collider
{
public:
	gravity_affected();
	bool weightless();
	void weightless(bool weightless);
	void handle_gravity();
private:
	bool _weightless;
};

#endif
