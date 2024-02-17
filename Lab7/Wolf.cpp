/*
 * Wolf.cpp
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#include "Wolf.h"

string Wolf::getType()
{
	return "Wolf";
}

void Wolf::drinkHealth()
{
	cout << "Wolf has drank Health" << endl;
	this->gainHealth(10);
}

void Wolf::drinkPoison()
{
	cout << "Wolf has drank Poison" << endl;
	this->hurtHealth(5);
}

void Wolf::drinkBeer()
{

	cout << "Wolf has drank Beer" << endl;
	this->hurtHealth(5);
}

void Wolf::fight(Creature &c)
{
	if(&c == NULL)
	{
		return;
	}
	string tmp = c.getType();
	if(tmp.compare("Penguin") == 0)
	{
		cout << "Wolf fought Penguin - Penguin has won" << endl;
		this->hurtHealth(50);
		c.gainHealth(20);
		return;
	}
	else if(tmp.compare("Troll") == 0)
	{
		cout << "Wolf fought Troll - Wolf has won" << endl;

		this->gainHealth(20);
		c.hurtHealth(50);
		return;
	}
	else if(tmp.compare("Wolf") == 0)
	{
		cout << "2 Wolf met - no fight" << endl;
		return;
	}
}
