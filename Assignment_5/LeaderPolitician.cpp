
#include "LeaderPolitician.h"

// Politician Constructor - requires Private and last names, a unique ID and political power
LeaderPolitician::LeaderPolitician(char *privateName, char *surName, int id, int power): Politician(privateName, surName, id, power) {}

// Politician Destructor
LeaderPolitician::~LeaderPolitician() {}

// Overwrite Politician::getPrimarisePower function
int LeaderPolitician::getPrimariesPower() const {
    return power;
}
// Overwrite Politician::getElectionPower function
int LeaderPolitician::getElectionPower() const {
    return Politician::getElectionPower();
}
    
// Print DemPolitician information
void LeaderPolitician::printPolitician() const {
    cout << ", Type:L, ";
}