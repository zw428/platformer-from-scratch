#ifndef LEDGE_GRABBER_H
#define LEDGE_GRABBER_H

class box;
class vel_accel;
class object;

class ledge_grabber
{
public:
	ledge_grabber();
	unsigned short dist_to_ledge() const;
	short h_dist_to_ledge() const;
	bool found_ledge() const;
	bool hanging() const;
	void find_ledge( object* obj, bool on_ground );
	void let_go();
private:
	void attach_to_ledge( vel_accel* va );

	unsigned short _dist_to_ledge;
	unsigned short _h_dist_to_ledge;
	bool _found_ledge;
	bool _letting_go;
	bool _hanging;
};

#endif
