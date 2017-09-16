#ifndef MOVER_H
#define MOVER_H

class mover
{
public:
	mover();

	unsigned short h_speed_max() const;
	void h_speed_max( unsigned short speed );

	float h_accel_rate() const;
	void h_accel_rate( float rate );

	float move_left( float h_speed );
	float move_right( float h_speed );

	bool facing_left() const;
	bool facing_right() const;
private:
	unsigned short _h_speed_max;
	float _h_accel_rate;
	bool _facing_right;
};

#endif
