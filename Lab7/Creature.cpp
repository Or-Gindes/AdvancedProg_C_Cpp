/*
 * Creature.cpp
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#include "Creature.h"

Creature::Creature()
{
	health_stat = 100;
}

void drinkHealth()
{

}

void drinkPoison()
{

}

void drinkBeer()
{

}

void Creature::hurtHealth(int amount)
{
	if(this->health_stat - amount < 0)
	{
		cout << "\tI have died!" << endl;
	}
	else
	{
		this->health_stat = this->health_stat - amount;
		cout << "	\t" << this->getType() << ": hurt for " << amount << " points" << endl;
	}
}
void Creature::gainHealth(int amount)
{
	if(this->health_stat == this->MAX_HEALTH)
	{
		return;
	}
	else if(this->health_stat+amount > this->MAX_HEALTH)
	{
		int gain = this->MAX_HEALTH - this->health_stat;
		this->health_stat+=gain;
		cout << "\t" << this->getType() << ": gained" << gain << "points" << endl;
	}
	else
	{
		int gain = this->health_stat + amount;
		cout << "\t" << this->getType() << ": gained " << amount << " points" << endl;
	}
}

Creature::~Creature()
{

}
