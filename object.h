#ifndef OBJECT_H
#define OBJECT_H

#include "box.h"

class object : virtual public box
{
public:
	object();
	virtual ~object();
	bool operator==(const object& obj);
	bool operator!=(const object& obj);
	virtual bool think() = 0;
	unsigned long id() const;
	void solid( bool solid );
	bool solid() const;
private:
	bool _solid;
	unsigned long _id;
	static unsigned long _id_counter;
};

#endif
