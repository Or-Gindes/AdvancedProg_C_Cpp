#ifndef REPUBLICANPOLITICIAN_H
#define REPUBLICANPOLITICIAN_H

#include "Politician.h"

// Inherent class from Politician where only which can only join republican parties
class RepublicanPolitician: virtual public Politician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    RepublicanPolitician(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~RepublicanPolitician();

    // Print Republican politician information
    virtual void printPolitician() const = 0;

    virtual bool canJoinDemocraticParty();
    virtual bool canJoinRepublicanParty();
};


#endif // REPUBLICANPOLITICIAN_H
