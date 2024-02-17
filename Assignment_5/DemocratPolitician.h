#ifndef DEMOCRATEPOLITICIAN_H
#define DEMOCRATEPOLITICIAN_H

#include "Politician.h"

// Inherent class from Politician where only which can only join democratic parties
class DemocratPolitician: virtual public Politician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    DemocratPolitician(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~DemocratPolitician();

    // Print DemPolitician information
    virtual void printPolitician() const = 0;

    virtual bool canJoinDemocraticParty();
    virtual bool canJoinRepublicanParty();
};


#endif //DEMOCRATEPOLITICIAN_H