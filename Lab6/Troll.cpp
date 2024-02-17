#include "Troll.h"

string Troll::getType()
{
	return "Troll";
}

void Troll::fight(Creature &other)
{
	if(&other == NULL){
		return;
	}
	string other_type = other.getType();
    // Troll loses to Wolf
	if(other_type.compare("Wolf") == 0)
	{
		cout << "Troll fought Wolf - Wolf has won" << endl;
		this->hurtHealth(50);
		other.gainHealth(20);
		return;
	}
    // Troll wins vs Penguin
	else if(other_type.compare("Penguin") == 0)
	{
		cout << "Troll fought Penguin - Troll has won" << endl;

		this->gainHealth(20);
		other.hurtHealth(50);
		return;
	}
    // Tie
	else if(other_type.compare("Troll") == 0)
	{
		cout << "2 Trolls met - no fight" << endl;
		return;
	}
}