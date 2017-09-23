#ifndef FRICTION_H
#define FRICTION_H

class friction
{
public:
	friction();

	void coefficient( float coeff );
	float coefficient();

	float friction_reduction( float speed );
private:
	float _coeff;
};

#endif
