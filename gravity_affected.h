#ifndef GRAVITY_AFFECTED_H
#define GRAVITY_AFFECTED_H

#include "vel_accel.h"

class gravity_affected
{
public:
	gravity_affected();
	bool weightless() const;
	void weightless(bool weightless);
	void apply_gravity(vel_accel& va, bool on_ground);
private:
	bool _weightless;
};

#endif
