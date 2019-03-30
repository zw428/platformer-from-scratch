#pragma once

#ifndef VEL_ACCEL_H
#define VEL_ACCEL_H

const float SPEED_MAX = 15;

class vel_accel
{
public:
	vel_accel();
	void h_speed(float h_speed);
	void v_speed(float v_speed);
	float h_speed() const;
	float v_speed() const;

	void h_accel(float h_accel);
	void v_accel(float v_accel);
	float h_accel() const;
	float v_accel() const;
private:
	float limit_speed( float speed );
	float _h_speed;
	float _v_speed;

	float _h_accel;
	float _v_accel;
};

#endif
