
#ifndef REPUBLICANPOLITICIANSOCIAL_H
#define REPUBLICANPOLITICIANSOCIAL_H
#include "RepublicanPolitician.h"
#include "SocialPolitician.h"

class RepublicanPoliticianSocial: public RepublicanPolitician, public SocialPolitician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    RepublicanPoliticianSocial(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~RepublicanPoliticianSocial();

    // Print RepublicanPoliticianSocial information
    virtual void printPolitician() const;
};


#endif //REPUBLICANPOLITICIANSOCIAL_H
