#ifndef FRICTION_H
#define FRICTION_H

#include "vel_accel.h"

class friction : public vel_accel
{
public:
	friction();

	void coefficient( float coeff );
	float coefficient();

	void apply_friction();
private:
	float _coeff;
};

#endif
