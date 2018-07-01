#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "delayed_attack_box.h"
#include "delayed_attack_bullet.h"
#include "attack_manager.h"

class player : public creature
{
public:
	player();
	~player();
	bool think_more();
	void load_data_from_file();
private:
	attack_manager _am;
};

#endif
