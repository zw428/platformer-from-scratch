#pragma once

#ifndef DELAYED_ACTION
#define DELAYED_ACTION

class delayed_action
{
public:
	delayed_action();
	void think( bool starting );
	void delay( unsigned short delay );
	void cooldown( unsigned short cooldown );
	unsigned short delay() const;
	unsigned short cooldown() const;
	bool acting() const;
	bool cooling_down() const;
	bool ready() const;
private:
	unsigned short _delay;
	unsigned short _delay_counter;

	unsigned short _cooldown;
	unsigned short _cooldown_counter;

	bool _acting;
	bool _ready;
};
#endif
