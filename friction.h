#ifndef FRICTION_H
#define FRICTION_H

class vel_accel;

class friction
{
public:
	friction();

	void coefficient( float coeff );
	float coefficient();

	void apply_friction( vel_accel& va);
private:
	float _coeff;
};

#endif
