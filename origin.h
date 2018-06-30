#pragma once

#ifndef ORIGIN_H
#define ORIGIN_H

#include "box.h"

enum origins 
{
	origin_top, origin_tr, origin_right, origin_br, origin_bottom,
	origin_bl, origin_left, origin_tl, origin_center
};

class origin
{
public:
	origin();
	void set_dir( origins o );
	origins dir() const;
	void apply( box& child, box parent );
private:
	origins _o;
};
#endif
