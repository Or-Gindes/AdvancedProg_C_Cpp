/*
 * Creature.h
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <string.h>
#include <iostream>
//#include "Potion.h"

using namespace std;

class Creature {
private:
	static const int MAX_HEALTH = 100;
protected:
	int health_stat;
public:
	Creature();

	void hurtHealth(int amount);
	void gainHealth(int amount);
	virtual void drinkHealth() = 0;
	virtual void drinkPoison() = 0;
	virtual void drinkBeer() = 0;

	virtual ~Creature();
	virtual string getType() = 0;
	virtual void fight(Creature &c) = 0;
};

#endif /* CREATURE_H_ */
