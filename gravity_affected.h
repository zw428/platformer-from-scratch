#ifndef GRAVITY_AFFECTED_H
#define GRAVITY_AFFECTED_H

#include "collider.h"
#include "teleporter.h"

class gravity_affected : public teleporter
{
public:
	gravity_affected();
	bool weightless() const;
	void weightless(bool weightless);
	void handle_gravity();
private:
	bool _weightless;
};

#endif
