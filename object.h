#ifndef OBJECT_H
#define OBJECT_H

#include "gravity_affected.h"

class object : public gravity_affected
{
public:
	object();
	virtual ~object();
	bool operator==(const object& obj);
	bool operator!=(const object& obj);
	virtual bool think() = 0;
	unsigned long id() const;
private:
	unsigned long _id;
	static unsigned long _id_counter;
};

#endif
