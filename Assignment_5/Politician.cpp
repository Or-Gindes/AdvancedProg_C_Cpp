
#include "Politician.h"


// Politician Constructor - requires Private and last names, a unique ID and political power.
// Party and chairman are initialized as nullptr
Politician::Politician(char *privateName, char *surName, int id, int power) : id(id), party(nullptr), chairman(nullptr), power(power) {
    this->privateName = new char[strlen(privateName) + 1];
    strcpy(this->privateName, privateName);
    this->surName = new char[strlen(surName) + 1];
    strcpy(this->surName, surName);
}

// Politician Destructor
Politician::~Politician() {
    delete[] this->privateName;
    delete[] this->surName;
}

// Returns Private Name of the Politician
char* Politician::getPrivateName() const {
    return privateName;
}

// Returns Last Name of the Politician
char* Politician::getSurName() const {
    return surName;
}

// Returns Politicians unique ID
int Politician::getId() const {
    return id;
}

// Return power for elections
int Politician::getElectionPower() const {
    return power;
}

// Return power for Primaries - Only LeaderPolitcians have power in the Primaries
int Politician::getPrimariesPower() const {
    return -1;
}

// Returns a pointer to the party the politician is currently part of
Party* Politician::getParty() const {
    return this->party;
}

// Change party association
void Politician::setParty(Party *party) {
    this->party = party;
}

// Update the identity of party chairman
void Politician::updateChairman(const Politician *chairman) {
    this->chairman = chairman;
}

// Print Politician information
void Politician::printPolitician() const {
    cout << "Person:" << privateName << " " << surName << ", Id:" << id << ", Power:" << power;
}

// Check if politicians have the same unique ID
bool Politician::operator==(const Politician &other) const {
    return this->id == other.id;
}
