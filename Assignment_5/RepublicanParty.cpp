
#include "RepublicanParty.h"

// Constructor - requires name like its parent class
RepublicanParty::RepublicanParty(char *name): Party(name) {}

RepublicanParty::~RepublicanParty() {}

// 1. Politician is able to join a republican party
// 2. Politician is not a member of any party
// 3. if this party is smaller than the party he's a member of (and would still be smaller if he transfered)
// check if one of them is true, if so add the republican politician to the party
bool RepublicanParty::addPolitician(Politician* politician) {
    if (!politician->canJoinRepublicanParty())
        return false;
    Party *current_party = politician->getParty();
    if (current_party == nullptr || current_party->getPartySize() > this->getPartySize()) {
        this->politicians.push_back(politician);
        politician->updateChairman(this->getChairman());
        // if politician joined the party he should be removed from his previous one (if a previous one existed)
        if (current_party != nullptr){
            current_party->removePolitician(*politician);
        }
        politician->setParty(this);
        return true;
    }
    return false;
}

// Print Republican party info followed by party memebers info
void RepublicanParty::printParty() const {
    char *chairman_name = (char*)"None";
    if (this->chairman != nullptr)
        chairman_name = this->chairman->getPrivateName();

    cout << "Republican Party: " << this->name << ", chairman:" << chairman_name << ", Size:" << this->getPartySize() << endl;
    Party::printParty();
}