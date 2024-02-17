
#include "SocialPolitician.h"

// Politician Constructor - requires Private and last names, a unique ID and political power
SocialPolitician::SocialPolitician(char *privateName, char *surName, int id, int power): Politician(privateName, surName, id, power) {}

// Politician Destructor
SocialPolitician::~SocialPolitician() {}

// Overwrite Politician::getElectionPower function
int SocialPolitician::getElectionPower() const {
    return power * 2;
}

// Overwrite Politician::getElectionPower function
int SocialPolitician::getPrimariesPower() const {
    return Politician::getPrimariesPower();
}
    
// Print DemPolitician information
void SocialPolitician::printPolitician() const {
    cout << ", Type:S, ";
}