#pragma once

#ifndef SPAWNABLE_H
#define SPAWNABLE_H

class spawnable
{
public:
	spawnable();
	virtual ~spawnable();
	void spawn();
	void handle_spawning();

	void spawn_delay( unsigned delay );
	unsigned spawn_delay() const;

	bool spawning() const;

	virtual void on_spawn() = 0;
private:
	unsigned _spawn_delay;
	unsigned _spawn_timer;
	bool _spawning;
};

#endif
