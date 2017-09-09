#ifndef ATTACKABLE_H
#define ATTACKABLE_H

class attack;

class attackable
{
public:
	attackable();
	~attackable();
	virtual void receive_attack( const attack& att ) = 0;
private:
};


#endif
