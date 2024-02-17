/*
 * Troll.cpp
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#include "Troll.h"

string Troll::getType()
{
	return "Troll";
}

void Troll::drinkHealth()
{
	cout << "Troll has drank Health" << endl;
	this->hurtHealth(10);

}

void Troll::drinkPoison()
{
	cout << "Troll has drank Poison" << endl;
	this->gainHealth(5);
}

void Troll::drinkBeer()
{
	cout << "Troll has drank Beer" << endl;
	this->gainHealth(5);
}

void Troll::fight(Creature &c)
{
	if(&c == NULL)
	{
		return;
	}
	string tmp = c.getType();
	if(tmp.compare("Penguin") == 0)
	{
		cout << "Troll fought Penguin - Troll has won" << endl;
		this->gainHealth(20);
		c.hurtHealth(50);
		return;
	}
	else if(tmp.compare("Wolf") == 0)
	{
		cout << "Troll fought Wolf - Wolf has won" << endl;

		this->hurtHealth(50);
		c.gainHealth(20);
		return;
	}
	else if(tmp.compare("Troll") == 0)
	{
		cout << "2 Troll met - no fight" << endl;
		return;
	}
}
