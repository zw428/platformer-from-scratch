#pragma once

#ifndef ENEMY_BASIC_H
#define ENEMY_BASIC_H

#include "creature.h"
#include "attack_manager.h"

class enemy_basic : public creature
{
public:
	enemy_basic();
	~enemy_basic();
	bool think_more();
	void load_data_from_file();
private:
};

#endif
