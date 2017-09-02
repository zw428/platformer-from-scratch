#ifndef MOVER_H
#define MOVER_H

#include "vel_accel.h"

class mover : public vel_accel
{
public:
	mover();

	unsigned short h_speed_max();
	void h_speed_max( unsigned short speed );

	unsigned short jump_vel();
	void jump_vel( unsigned short speed );

	float h_accel_rate();
	void h_accel_rate( float rate );

	void move_left();
	void move_right();
	void jump();
private:
	unsigned short _h_speed_max;
	float _h_accel_rate;
	unsigned short _jump_vel;
};

#endif
