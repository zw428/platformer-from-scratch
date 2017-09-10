#ifndef JUMPER_H
#define JUMPER_H

#include "gravity_affected.h"

class jumper : public gravity_affected
{
public:
	jumper();

	void jump_vel_1( unsigned short speed );
	void jump_vel_2( unsigned short speed );
	unsigned short jump_vel_1() const;
	unsigned short jump_vel_2() const;

	unsigned short times_jumped() const;

	void handle_jumping( bool jumping ); //jumping == jump key is pressed
private:
	void jump( bool first );
	unsigned short _jump_vel_1;
	unsigned short _jump_vel_2;

	unsigned short _times_jumped;

	bool _jump_released;
};

#endif
