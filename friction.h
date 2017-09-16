#ifndef FRICTION_H
#define FRICTION_H

class friction
{
public:
	friction();

	void coefficient( float coeff );
	float coefficient();

	float friction_reduction( float h_speed );
private:
	float _coeff;
};

#endif
