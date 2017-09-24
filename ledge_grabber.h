#ifndef LEDGE_GRABBER_H
#define LEDGE_GRABBER_H

class box;

class ledge_grabber
{
public:
	ledge_grabber();
	unsigned short dist_to_ledge() const;
	short h_dist_to_ledge() const;
	bool found_ledge() const;
	void find_ledge( box* b );
	void let_go();
private:
	unsigned short _dist_to_ledge;
	unsigned short _h_dist_to_ledge;
	bool _found_ledge;
	bool _letting_go;
};

#endif
