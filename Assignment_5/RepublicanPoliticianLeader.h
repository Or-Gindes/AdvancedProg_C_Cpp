
#ifndef REPUBLICANPOLITICIANLEADER_H
#define REPUBLICANPOLITICIANLEADER_H
#include "RepublicanPolitician.h"
#include "LeaderPolitician.h"

class RepublicanPoliticianLeader : public RepublicanPolitician, public LeaderPolitician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    RepublicanPoliticianLeader(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~RepublicanPoliticianLeader();

    // Print RepublicanPoliticianLeader information
    virtual void printPolitician() const;
};


#endif //REPUBLICANPOLITICIANLEADER_H
