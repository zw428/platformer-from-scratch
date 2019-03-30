#pragma once

#ifndef ATTACKABLE_H
#define ATTACKABLE_H

#include "attack.h"
#include "box_object.h"

enum attackable_type
{
	attackable_invincible, attackable_knockback_multiplier, attackable_health
};

class attackable : public box_object
{
public:
	attackable();
	~attackable();
	virtual void receive_attack( const attack& att );
	virtual bool think_more();

	void health( unsigned short health );
	unsigned short health() const;

	void type( attackable_type t );
	attackable_type type() const;
private:
	void attacked_health( const attack& att );
	void attacked_knockback_multiplier( const attack& att );
	attackable_type _at;
	unsigned short _health;
};

#endif
