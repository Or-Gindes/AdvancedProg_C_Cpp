#ifndef DEMOCRATEPOLITICIANSOCIAL_H
#define DEMOCRATEPOLITICIANSOCIAL_H
#include "DemocratPolitician.h"
#include "SocialPolitician.h"

class DemocratPoliticianSocial: public DemocratPolitician, public SocialPolitician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    DemocratPoliticianSocial(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~DemocratPoliticianSocial();

    // Print DemPoliticianSocial information
    virtual void printPolitician() const;
};


#endif // DEMOCRATEPOLITICIANSOCIAL_H
