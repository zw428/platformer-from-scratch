#ifndef ATTACK_MANAGER_H
#define ATTACK_MANAGER_H

#include <memory>
#include "delayed_attack.h"

class attack_manager
{
public:
	attack_manager();

	void think(bool attacking, unsigned short direction, bool special, bool in_air);

	void set_up_attack(delayed_attack* da);
	void set_down_attack(delayed_attack* da);
	void set_right_attack(delayed_attack* da);

	void set_up_air_attack(delayed_attack* da);
	void set_down_air_attack(delayed_attack* da);
	void set_right_air_attack(delayed_attack* da);

	void set_up_special_attack(delayed_attack* da);
	void set_down_special_attack(delayed_attack* da);
	void set_right_special_attack(delayed_attack* da);

	bool can_move() const;
private:
	void attack(unsigned short direction, bool special, bool in_air);

	delayed_attack* _current_attack;
	bool _can_move;

	std::shared_ptr<delayed_attack> _up_attack;
	std::shared_ptr<delayed_attack> _down_attack;
	std::shared_ptr<delayed_attack> _right_attack;

	std::shared_ptr<delayed_attack> _up_air_attack;
	std::shared_ptr<delayed_attack> _down_air_attack;
	std::shared_ptr<delayed_attack> _right_air_attack;

	std::shared_ptr<delayed_attack> _up_special_attack;
	std::shared_ptr<delayed_attack> _down_special_attack;
	std::shared_ptr<delayed_attack> _right_special_attack;
};

#endif
