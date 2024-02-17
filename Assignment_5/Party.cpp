
#include "Party.h"

// Default Constructor - party has no chairman on creation and will print "None"
Party::Party(char *name) : chairman(nullptr) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Politicians are cleared by the PoliticalSys 
Party::~Party() {
    delete[] this->name;
    politicians.clear();
}

// Remove a Politician from the the party if he is found in it
void Party::removePolitician(const Politician& politician) {
    vector<Politician *>::iterator pol_it;
    for (pol_it = politicians.begin(); pol_it != politicians.end(); ++pol_it) {
        if ((**pol_it) == politician) {
            // If the removed politician is the chairman, the party is left without one and must update its observers
            if ((*pol_it) == chairman) {
                this->chairman = nullptr;
                notifyPoliticians();
            }
            // Clear politician party & chairman pointer and remove from the party vector
            (*pol_it)->setParty(nullptr);
            (*pol_it)->updateChairman(nullptr);
            politicians.erase(pol_it);
            
            return;
        }
    }
    // throw invalid ID exception if id isn't found in party
    throw InvalidID();
}

// Perform Primarise and elect a chairman out of leader politicians in the party
void Party::Primaries() {
    Politician *candidate = chairman;
    int max_power = 0;
    vector<Politician *>::iterator pol_it;
    for (pol_it = politicians.begin(); pol_it != politicians.end(); ++pol_it) {
        if ((*pol_it)->getPrimariesPower() > max_power){
            candidate = *pol_it;
            max_power = candidate->getPrimariesPower();
        }
    }
    chairman = candidate;
    notifyPoliticians();
    if (chairman == nullptr)
        cout << "None";
    else
        cout << chairman->getPrivateName();
    cout << " is the chairman of " << this->name << endl;
}

// Update each politician in the party on the new chairman
void Party::notifyPoliticians() const {
    vector<Politician *>::const_iterator pol_it;
    for (pol_it = politicians.begin(); pol_it != politicians.end(); ++pol_it)
        (*pol_it)->updateChairman(chairman);
}

// Calculate the power of the party for elections - Iterate over members of the party and sum their election power to get the power of the party
int Party::getPartyPower() const {
	int partyPower = 0;
    vector<Politician *>::const_iterator pol_it;
    for (pol_it = politicians.begin(); pol_it != politicians.end(); ++pol_it)
        partyPower += (*pol_it)->getElectionPower();

    cout << "Party: " << this->name << ",Power: " << partyPower << endl;
    return partyPower;
}

// Returns the number of politicians in the party
int Party::getPartySize() const {
	return politicians.size();
}

// Returns the name of the party
char* Party::getName() const {
    return name;
}

// Returns a reference to the chairman of the party
const Politician* Party::getChairman() const {
    return chairman;
}

// Returns vector of party politicians
const vector <Politician*> &Party::getPoliticians() const {
    return politicians;
}

// Print Politicians in the party
void Party::printParty() const {
    vector<Politician *>::const_iterator pol_it;
    for (pol_it = politicians.begin(); pol_it != politicians.end(); ++pol_it){
        cout << "\t";
        (*pol_it)->printPolitician();
    }
}

/* static method which compares two parties using the operator< */
bool Party::compareParties(Party* party1, Party *party2) {
    if (party1->politicians.size() < party2->politicians.size())
        return true;
    
    else if (party1->politicians.size() == party2->politicians.size()) {
        if (strcmp(party1->name, party2->name) < 0)
            return true;
    }
    
    return false;
}