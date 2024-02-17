#include <iostream>
#include "Creature.h"
#include "Wolf.h"
#include "Troll.h"
#include "Penguin.h"
#include "Potion.h"
#include "Health.h"
#include "Poison.h"
#include "Beer.h"

using namespace std;

int main()
{
	Wolf w1;
	Penguin p1;
	Troll t1;

	Creature *creatures[3];
	creatures[0] = &w1;		creatures[1] = &p1;		creatures[2] = &t1;


	Health h;
	Poison p;
	Beer b;

	Potion *potions[3];
	potions[0]=&h;	potions[1]=&p;	potions[2]=&b;

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			potions[j]->drink(*creatures[i]);
		}
	}

	return 0;
}
