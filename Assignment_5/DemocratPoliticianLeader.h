
#ifndef DEMOCRATEPOLITICIANLEADER_H
#define DEMOCRATEPOLITICIANLEADER_H
#include "DemocratPolitician.h"
#include "LeaderPolitician.h"

class DemocratPoliticianLeader: public DemocratPolitician, public LeaderPolitician {
public:
    // Politician Constructor - requires Private and last names, a unique ID and political power
    DemocratPoliticianLeader(char *privateName, char *surName, int id, int power);

    // Politician Destructor
    virtual ~DemocratPoliticianLeader();

    // Print DemPoliticianLeader information
    virtual void printPolitician() const;
};


#endif // DEMOCRATEPOLITICIANLEADER_H
