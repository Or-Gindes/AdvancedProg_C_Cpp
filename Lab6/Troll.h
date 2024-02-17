#ifndef TROLL_H_
#define TROLL_H_

#include "Creature.h"

using namespace std;

class Troll: public Creature 
{
public:
	Troll(){};
	virtual ~Troll(){};
	virtual string getType();
	virtual void fight(Creature &other);
};

#endif /* TROLL_H_ */