#pragma once

#ifndef DELAYED_ATTACK_BOX_H
#define DELAYED_ATTACK_BOX_H

#include <string>
#include "delayed_attack.h"

class delayed_attack_box : public delayed_attack
{
public:
	delayed_attack_box();
	~delayed_attack_box();
	void perform();
	unsigned short lifespan() const;
	void lifespan(unsigned short t);
	box dimens;
	coords offset;
	bool add_as_child;
	void load_data_from_file(std::string path);
private:
	unsigned short _lifespan;
};

#endif
