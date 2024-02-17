#ifndef WOLF_H_
#define WOLF_H_

#include "Creature.h"

using namespace std;

class Wolf: public Creature 
{
public:
	Wolf(){};
	virtual ~Wolf(){};
	virtual string getType();
	virtual void fight(Creature &other);
};

#endif /* WOLF_H_ */