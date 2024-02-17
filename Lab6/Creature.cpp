#include "Creature.h"

Creature::Creature()
{
    health_stat = 100;
}

void Creature::hurtHealth(int damage)
{
    if(health_stat - damage < 0){
		cout << "\t" << getType() << ": I have died!" << endl;
	}
	else{
		health_stat -= damage;
		cout << "\t" << getType() << ": hurt for " << damage << " points" << endl;
	}
}

void Creature::gainHealth(int heal)
{
    // no health gained
    if (health_stat == MAX_HEALTH)
        return;

    // health stat + heal isn't larger than MAX_HEALTH -> gain all healing
    else if(health_stat + heal <= MAX_HEALTH){
        health_stat += heal;
        cout << "\t" << getType() << ": gained " << heal << " points" << endl;
    }
    // Gain partial healing up to MAX_HEALTH
    else{
        cout << "\t" << getType() << ": gained " << MAX_HEALTH - health_stat << " points" << endl;
        health_stat = MAX_HEALTH;
    }
}
