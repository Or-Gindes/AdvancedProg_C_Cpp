#ifndef CREATURE_H_
#define CREATURE_H_

#include <iostream>
#include <string.h>

using namespace std;

class Creature
{
private:
    static const int MAX_HEALTH = 100;
protected:
    int health_stat;

public:
    // Common methods
    Creature();
    void hurtHealth(int damage);
    void gainHealth(int heal);

    // Virtual methods to be implemented by inheriters
    virtual ~Creature(){};
    virtual string getType() = 0;
    virtual void fight(Creature &other) = 0;
};
#endif /* CREATURE_H_ */