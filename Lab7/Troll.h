/*
 * Troll.h
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#ifndef TROLL_H_
#define TROLL_H_

#include <string.h>
#include <iostream>
#include "Creature.h"

using namespace std;

class Troll: public Creature {
public:
	Troll(){};
public:
	void drinkHealth();
	void drinkPoison();
	void drinkBeer();
	void fight(Creature &c);

	virtual ~Troll(){};
	virtual string getType();
};

#endif /* TROLL_H_ */
