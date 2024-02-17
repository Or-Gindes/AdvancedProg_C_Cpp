
#include "DemocratPolitician.h"

// Politician Constructor - requires Private and last names, a unique ID and political power
DemocratPolitician::DemocratPolitician(char *privateName, char *surName, int id, int power): Politician(privateName, surName, id, power) {}

// Politician Destructor
DemocratPolitician::~DemocratPolitician() {}

// Print DemPolitician information
void DemocratPolitician::printPolitician() const {
    cout << "Democratic ";
}

// join Democratic party
bool DemocratPolitician::canJoinDemocraticParty() {
    return true;
}

// join Republican party - always false
bool DemocratPolitician::canJoinRepublicanParty() {
    return false;
}