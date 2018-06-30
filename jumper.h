#pragma once

#ifndef JUMPER_H
#define JUMPER_H

class jumper
{
public:
	jumper();

	void jump_vel_1( unsigned short speed );
	void jump_vel_2( unsigned short speed );
	unsigned short jump_vel_1() const;
	unsigned short jump_vel_2() const;

	unsigned short times_jumped() const;

	short handle_jumping( bool on_ground, bool jumping ); //jumping == jump key is pressed
private:
	short jump( bool first );
	unsigned short _jump_vel_1;
	unsigned short _jump_vel_2;

	unsigned short _times_jumped;

	bool _jump_released;
};

#endif
