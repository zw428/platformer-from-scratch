#ifndef MOVABLE_H
#define MOVABLE_H

class movable
{
public:
	movable();
	void h_speed(float h_speed);
	void v_speed(float v_speed);
	float h_speed();
	float v_speed();
private:
	float _h_speed;
	float _v_speed;
};

#endif
