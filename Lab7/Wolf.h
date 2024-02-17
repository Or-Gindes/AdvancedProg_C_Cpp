/*
 * Wolf.h
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#ifndef WOLF_H_
#define WOLF_H_

#include <string.h>
#include <iostream>
#include "Creature.h"

using namespace std;

class Wolf: public Creature {
public:
	Wolf(){};
public:
	void drinkHealth();
	void drinkPoison();
	void drinkBeer();
	void fight(Creature &c);

	virtual ~Wolf(){};
	virtual string getType();
};

#endif /* WOLF_H_ */
