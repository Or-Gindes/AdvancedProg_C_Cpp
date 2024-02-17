#ifndef PENGUIN_H_
#define PENGUIN_H_

#include "Creature.h"

using namespace std;

class Penguin: public Creature 
{
public:
	Penguin(){};
	virtual ~Penguin(){};
	virtual string getType();
	virtual void fight(Creature &other);
};

#endif /* PENGUIN_H_ */