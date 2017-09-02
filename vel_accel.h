#ifndef VEL_ACCEL_H
#define VEL_ACCEL_H

class vel_accel
{
public:
	vel_accel();
	void h_speed(float h_speed);
	void v_speed(float v_speed);
	float h_speed();
	float v_speed();

	void h_accel(float h_accel);
	void v_accel(float v_accel);
	float h_accel();
	float v_accel();
private:
	float _h_speed;
	float _v_speed;

	float _h_accel;
	float _v_accel;
};

#endif
