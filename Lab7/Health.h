#include "Potion.h"

using namespace std;

class Health: public Potion {
public:
	virtual void drink(Creature &creatures){creatures.drinkHealth();};
};

