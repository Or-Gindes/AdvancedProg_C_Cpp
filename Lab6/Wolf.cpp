#include "Wolf.h"

string Wolf::getType()
{
	return "Wolf";
}

void Wolf::fight(Creature &other)
{
	if(&other == NULL){
		return;
	}
	string other_type = other.getType();
    // Wolf loses to Penguins
	if(other_type.compare("Penguin") == 0)
	{
		cout << "Wolf fought Penguin - Penguin has won" << endl;
		this->hurtHealth(50);
		other.gainHealth(20);
		return;
	}
    // Wolf wins vs Troll
	else if(other_type.compare("Troll") == 0)
	{
		cout << "Wolf fought Troll - Wolf has won" << endl;

		this->gainHealth(20);
		other.hurtHealth(50);
		return;
	}
    // Tie
	else if(other_type.compare("Wolf") == 0)
	{
		cout << "2 Wolves met - no fight" << endl;
		return;
	}
}