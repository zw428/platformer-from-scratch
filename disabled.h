#ifndef DISABLED_H
#define DISABLED_H

class disabled
{
public:
	disabled();
	void handle_disabled();
	bool is_disabled();
	void disable( unsigned time );
private:
	unsigned _timer;
};

#endif
