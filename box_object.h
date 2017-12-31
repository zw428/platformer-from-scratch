#ifndef BOX_OBJECT_H
#define BOX_OBJECT_H

#include "object.h"
#include "box.h"
#include "vel_accel.h"

class box_object : public object
{
public:
	box_object();
	virtual bool think();
	box dimens;
	vel_accel speeds;
	bool solid() const;
	void solid( bool solid );
private:
	bool _solid;
};

#endif
