#ifndef DEATH_BOX_H
#define DEATH_BOX_H

#include "trigger.h"
class object;

class death_box : public trigger
{
public:
	death_box();
	~death_box();

	bool action(object* obj);
private:
};

#endif
