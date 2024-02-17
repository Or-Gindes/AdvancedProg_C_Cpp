
#ifndef LEADER_H
#define LEADER_H

#include "Politician.h"

class LeaderPolitician: virtual public Politician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    LeaderPolitician(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~LeaderPolitician();

    // Overwrite Politician::getElectionPower function
    virtual int getElectionPower() const;
    // Overwrite Politician::getPrimarisePower function
    virtual int getPrimariesPower() const;

    // Print Leader information
    virtual void printPolitician() const = 0;
};


#endif //LEADER_H
