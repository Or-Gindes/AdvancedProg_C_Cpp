#include "Potion.h"

using namespace std;

class Beer: public Potion {
public:
	virtual void drink(Creature &creatures){creatures.drinkBeer();};
};

