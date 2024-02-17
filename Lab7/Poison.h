#include "Potion.h"

using namespace std;

class Poison: public Potion {
public:
	 virtual void drink(Creature &creatures){creatures.drinkPoison();};
};

