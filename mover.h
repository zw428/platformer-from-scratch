#ifndef MOVER_H
#define MOVER_H

class vel_accel;

class mover
{
public:
	mover();

	unsigned short h_speed_max() const;
	void h_speed_max( unsigned short speed );

	float h_accel_rate() const;
	void h_accel_rate( float rate );

	void move_left( vel_accel* va );
	void move_right( vel_accel* va );

	bool facing_left() const;
	bool facing_right() const;
private:
	unsigned short _h_speed_max;
	float _h_accel_rate;
	bool _facing_right;
};

#endif
