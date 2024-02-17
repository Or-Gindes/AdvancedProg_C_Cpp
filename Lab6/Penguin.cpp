#include "Penguin.h"

string Penguin::getType()
{
	return "Penguin";
}

void Penguin::fight(Creature &other)
{
	if(&other == NULL){
		return;
	}
	string other_type = other.getType();
    // Penguin loses to Troll
	if(other_type.compare("Troll") == 0)
	{
		cout << "Penguin fought Troll - Troll has won" << endl;
		this->hurtHealth(50);
		other.gainHealth(20);
		return;
	}
    // Penguin wins vs Wolf
	else if(other_type.compare("Wolf") == 0)
	{
		cout << "Penguin fought Wolf - Penguin has won" << endl;

		this->gainHealth(20);
		other.hurtHealth(50);
		return;
	}
    // Tie
	else if(other_type.compare("Penguin") == 0)
	{
		cout << "2 Penguins met - no fight" << endl;
		return;
	}
}