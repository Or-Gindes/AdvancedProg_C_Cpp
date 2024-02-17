
#ifndef SOCIAL_H
#define SOCIAL_H

#include "Politician.h"

class SocialPolitician: virtual public Politician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    SocialPolitician(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~SocialPolitician();

    // Overwrite Politician::getElectionPower function
    virtual int getElectionPower() const;
    // Overwrite Politician::getPrimarisePower function
    virtual int getPrimariesPower() const;

    // Print Leader information
    virtual void printPolitician() const = 0;
};


#endif //SOCIAL_H
