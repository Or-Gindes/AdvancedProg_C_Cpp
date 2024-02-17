#include <iostream>
using namespace std;
#include "Wolf.h"
#include "Troll.h"
#include "Penguin.h"



int main()
{
	Wolf w1, w2;
	Penguin p1, p2;
	Troll t1;

	//creatures
	Creature *creatures[5];
	creatures[0] = &w1;
	creatures[1] = &p1;
	creatures[2] = &t1;
	creatures[3] = &w2;
	creatures[4] = &p2;

	for (int i=0; i<5; i++)
	{
		for (int j=i+1; j<5; j++)
		{
			creatures[i]->fight(*creatures[j]);
		}
	}

	creatures[0]->fight(*creatures[1]);
	return 0;
}
