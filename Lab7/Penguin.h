/*
 * Penguin.h
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#ifndef PENGUIN_H_
#define PENGUIN_H_

#include <string.h>
#include <iostream>
#include "Creature.h"

using namespace std;

class Penguin: public Creature {
public:
	Penguin(){};
public:
	void fight(Creature &c);
	void drinkHealth();
	void drinkPoison();
	void drinkBeer();

	virtual ~Penguin(){};
	virtual string getType();
};

#endif /* PENGUIN_H_ */
