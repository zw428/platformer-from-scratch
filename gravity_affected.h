#ifndef GRAVITY_AFFECTED_H
#define GRAVITY_AFFECTED_H

class gravity_affected
{
public:
	gravity_affected();
	bool weightless() const;
	void weightless(bool weightless);
	double gravity_accel( bool on_ground );
private:
	bool _weightless;
};

#endif
