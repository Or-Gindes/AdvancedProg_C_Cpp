#ifndef POLITICIAN_H
#define POLITICIAN_H

#include "Defs.h"
#include "Party.h"


// Forward declartion of Party class
class Party;

// This generic Politician class sets up basic Politician functions

class Politician {
private:
    char* privateName;
    char* surName;
    const int id;
    Party *party;                       // A Pointer to the party of the politician 
    
protected:
    const Politician* chairman;         // A Pointer to the chairman of the party
    int power;

public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    Politician(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~Politician();

    // Returns Private Name of the Politician
    char* getPrivateName() const;

    // Returns Last Name of the Politician
    char* getSurName() const;

    // Returns Politicians unique ID
    int getId() const;

    // Returns Politician power for elections - different implementation for diffferent types of leaders
    virtual int getElectionPower() const = 0;

    // Returns Politician power for primaries - different implementation for diffferent types of leaders
    virtual int getPrimariesPower() const = 0;

    // Returns a pointer to the party the politician is currently part of (incase he needs to be removed from it)
    Party* getParty() const;

    // Change party association
    void setParty(Party *party);

    // Update the identity of party chairman
    void updateChairman(const Politician *chairman);

    // Print Politician information
    virtual void printPolitician() const = 0;

    // Check if politicians have the same unique ID
    bool operator==(const Politician &other) const;

    // Virtual join party function for each party type
    virtual bool canJoinDemocraticParty() = 0;
    virtual bool canJoinRepublicanParty() = 0;
};


#endif //POLITICIAN_H
