/*
 * Penguin.cpp
 *
 *  Created on: Dec 24, 2018
 *      Author: ise
 */

#include "Penguin.h"

string Penguin::getType()
{
	return "Penguin";
}

void Penguin::drinkHealth()
{
	cout << "Penguin has drank Health" << endl;
	this->gainHealth(5);
}

void Penguin::drinkPoison()
{
	cout << "Penguin has drank Poison" << endl;
	this->hurtHealth(10);
}

void Penguin::drinkBeer()
{
	cout << "Penguin has drank Beer" << endl;
	this->gainHealth(5);
}

void Penguin::fight(Creature &c)
{
	if(&c == NULL)
	{
		return;
	}
	string tmp = c.getType();
	if(tmp.compare("Wolf") == 0)
	{
		cout << "Penguin fought Wolf - Penguin has won" << endl;
		this->gainHealth(20);
		c.hurtHealth(50);
		return;
	}
	else if(tmp.compare("Troll") == 0)
	{
		cout << "Penguin fought Troll - Troll has won" << endl;

		this->hurtHealth(50);
		c.gainHealth(20);
		return;
	}
	else if(tmp.compare("Penguin") == 0)
	{
		cout << "2 Penguin met - no fight" << endl;
		return;
	}
}
