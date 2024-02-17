
#include "RepublicanPolitician.h"

// Politician Constructor - requires Private and last names, a unique ID and political power
RepublicanPolitician::RepublicanPolitician(char *privateName, char *surName, int id, int power): Politician(privateName, surName, id, power) {}

// Politician Destructor
RepublicanPolitician::~RepublicanPolitician() {}

// Print DemPolitician information
void RepublicanPolitician::printPolitician() const {
    cout << "Republican ";
}

// join Democratic party - always false
bool RepublicanPolitician::canJoinDemocraticParty() {
    return false;
}

// join Republican party 
bool RepublicanPolitician::canJoinRepublicanParty() {
    return true;
}