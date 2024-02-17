#include "PoliticalSys.h"



/* PoliticalSys Constructor - File path might be NULL file might be empty */
PoliticalSys::PoliticalSys(char *configFilePath) {
    // vector<Politician*> politicians;
    // vector<Party*> parties;
    if (configFilePath == NULL)
        return;

    ifstream conf_file;
    conf_file.open(configFilePath);
    if (conf_file.is_open()) {
        string line;
        char buffer[300];
        bool politician_rows = false;
        bool party_rows = false;
        char* name = NULL;
        char* surName = NULL;
        int id, power;
        char *party = NULL;
        char *type = NULL;
        while (getline(conf_file, line)){
            if (line == "Parties:\r"){
                party_rows = true;
                politician_rows = false;
                continue;
            }
            else if (line == "Politicians:\r"){
                party_rows = false;
                politician_rows = true;
                continue;
            }
            else if (politician_rows == true){
                strcpy(buffer, line.c_str());
                name = strtok(buffer, " ");
                surName = strtok(NULL, " ");
                id = atoi(strtok(NULL, " "));
                power = atoi(strtok(NULL, " "));
                party = strtok(NULL, " ");
                type = strtok(NULL, "\r");
                try {
                    addPolitician2Sys(name, surName, id, power, party[0], type[0]);
                } // Input in configuration file is assumed to be valid so no need to catch input exceptions here but memory problems can still happen
                catch (bad_alloc& ba) {
                    cout << "Memory Problem" << endl;
                    delete this;
                    exit(-1);
                } 
            }
            else if (party_rows == true){
                strcpy(buffer, line.c_str());
                name = strtok(buffer, " ");
                type = strtok(NULL, "\r");
                try {
                    addParty2Sys(name, type[0]);
                }
                catch (bad_alloc& ba) {
                    cout << "Memory Problem" << endl;
                    delete this;
                    exit(-1);
                } 
            }           
        }
    }
    conf_file.close();
    largest_party = (*max_element(parties.begin(), parties.end(), Party::compareParties));
}

/* Destructor - will free memory allocated to each politician and each party created in the political system */
PoliticalSys::~PoliticalSys() {
    vector<Politician *>::iterator pol_iter;
    for (pol_iter = politicians.begin(); pol_iter != politicians.end(); ++pol_iter)
        delete *pol_iter;
    politicians.clear();

    vector<Party *>::iterator party_iter;
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter)
        delete *party_iter;
    parties.clear();
}

/* Support function to add politicians to the system and find a party for them - handles all input validation checks and throws appropriate exceptions */
void PoliticalSys::addPolitician2Sys(char *firstName, char *surName, int ID, int power, char partyKind, char politicianKind){
    // ID Must be positive number
    if (ID <= 0)            
        throw InvalidID();
    
    // ID Must be unique
    vector<Politician *>::iterator pol_iter;
    for (pol_iter = politicians.begin(); pol_iter != politicians.end(); ++pol_iter){
        if ((*pol_iter)->getId() == ID)
            throw InvalidID();
    }
    // Power must be non-negative
    if (power < 0)
        throw InvalidInput();
    
    Politician* new_politician = nullptr;
    if (partyKind == 'R' && politicianKind == 'L') {
        new_politician = new RepublicanPoliticianLeader(firstName, surName, ID, power);

    } else if (partyKind == 'R' && politicianKind == 'S') {
        new_politician = new RepublicanPoliticianSocial(firstName, surName, ID, power);

    } else if (partyKind == 'D' && politicianKind == 'L') {
        new_politician = new DemocratPoliticianLeader(firstName, surName, ID, power);

    } else if (partyKind == 'D' && politicianKind == 'S') {
        new_politician = new DemocratPoliticianSocial(firstName, surName, ID, power);
        
    } else {    // PartyKind must be {'R','D'} and PoliticianKind must be {'L', 'S'} otherwise invalid input exception is thrown
        throw InvalidInput();
    }
    if (new_politician != nullptr) {
        findPartyForPolitician(new_politician);
        politicians.push_back(new_politician);
    }
}

void PoliticalSys::addPolitician() {
    string input;
    int ID, power;
    char partyKind, politicianKind;
    cout << "---Create Politician---\n";
    while (1) {
        try {
            cout << "First name:\n";
            cin >> input;
            char firstName[input.length() + 1];
            strcpy(firstName, input.c_str());
            cout << "Last name:\n";
            cin >> input;
            char surName[input.length() + 1];
            strcpy(surName, input.c_str());
            cout << "ID:\n";
            cin >> ID;
            cout << "Power:\n";
            cin >> power;
            cout << "Republican or Democratic person\n";
            cin >> partyKind;
            cout << "Leader or Social\n";
            cin >> politicianKind;
            addPolitician2Sys(firstName, surName, ID, power, partyKind, politicianKind);
            largest_party = (*max_element(parties.begin(), parties.end(), Party::compareParties));
            break;                                  // This is only reached if no exception was thrown
        }
        catch (bad_alloc& ba) {
            cout << "Memory Problem" << endl;
            delete this;
            exit(-1);
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

/* iterate parties and give the politician an option to join each one */
void PoliticalSys::findPartyForPolitician(Politician* politician) {
    vector<Party *>::iterator party_iter;
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter) {
        (*party_iter)->addPolitician(politician);
    }
}

/* Support function which adds a party to the system and handles all input validation */
void PoliticalSys::addParty2Sys(char *name, char partyKind) {
    // party name must be unique
    vector<Party *>::iterator party_iter;
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter){
        if (strcmp((*party_iter)->getName(), name) == 0)
            throw InvalidName();
    }
    if (partyKind == 'R') 
        addPolitician2Party(new RepublicanParty(name));

    else if (partyKind == 'D') 
        addPolitician2Party(new DemocraticParty(name));
        
    else {    // PartyKind must be {'R','D'} otherwise invalid input exception is thrown
        throw InvalidInput();
    }
}

/* Iterate politicians and give them the option of joining the party */
void PoliticalSys::addPolitician2Party(Party* party) {
    vector<Politician *>::iterator pol_iter;
    parties.push_back(party);
    for (pol_iter = politicians.begin(); pol_iter != politicians.end(); ++pol_iter)
        party->addPolitician(*pol_iter);
}

/* Create a new party, add it to the system and allow politicians to join */
void PoliticalSys::addParty() {
    string input;
    char *name = NULL;
    char partyKind;
    cout << "---Create Party---\n";
    while (1) {
        try {
            cout << "Name: \n";
            cin >> input;
            char name[input.length() + 1];
            strcpy(name, input.c_str());
            cout << "Republican or Democratic party \n";
            cin >> partyKind;
            addParty2Sys(name, partyKind);
            largest_party = (*max_element(parties.begin(), parties.end(), Party::compareParties));
            break;  // This is only reached if no exception was thrown
        }
        catch (bad_alloc& ba) {
            cout << "Memory Problem" << endl;
            delete this;
            exit(-1);
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

void PoliticalSys::removePolitician() {
    if (politicians.size() == 0)
        return;
    int ID;
    vector<Politician *>::iterator pol_iter;
    cout << "---Remove Politician---\n";
    while (1) {
        try {
            cout << "ID: \n";
            cin >> ID;
            // ID Must be positive number
            if (ID <= 0)            
                throw InvalidID();
            
            for (pol_iter = politicians.begin(); pol_iter != politicians.end(); ++pol_iter){
                if ((*pol_iter)->getId() == ID){
                    if ((*pol_iter)->getParty() != nullptr) {   // Verify the politician is actually in a party to begin with
                        (*pol_iter)->getParty()->removePolitician(**pol_iter);
                    }
                    delete *pol_iter;
                    politicians.erase(pol_iter);
                    largest_party = (*max_element(parties.begin(), parties.end(), Party::compareParties));
                    return;             // Politician was found and was removed from his party (or wasn't in a party to begin with) and from the system
                }
            }
            throw InvalidID();          // Politician Id was not found so InvalidID exception is thrown
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

void PoliticalSys::removeParty() {
    if (parties.size() == 0)
        return;
    string input;
    vector<Party *>::iterator parties_iter;
    cout << "---Remove Party---\n";
    while (1) {
        try {
            cout << "Enter party name: \n";
            cin >> input;
            for (parties_iter = parties.begin(); parties_iter != parties.end(); ++parties_iter){
                if (strcmp((*parties_iter)->getName(), input.c_str()) == 0){
                    // Iterate over politicians in the removed party and find them a new one
                    if ((*parties_iter)->getPoliticians().size() != 0) {
                        vector<Party *>::iterator inner_parties_iter;
                        vector<Politician *>::const_iterator pol_iter;
                        for (pol_iter = (*parties_iter)->getPoliticians().begin(); pol_iter != (*parties_iter)->getPoliticians().end(); ++pol_iter) {
                            (*pol_iter)->setParty(nullptr);
                            (*pol_iter)->updateChairman(nullptr);
                            for (inner_parties_iter = parties.begin(); inner_parties_iter != parties.end(); ++inner_parties_iter) {
                                if (strcmp((*inner_parties_iter)->getName(), (*parties_iter)->getName()) != 0)
                                    (*inner_parties_iter)->addPolitician(*pol_iter);
                            }
                        }
                    }
                    delete *parties_iter;
                    parties.erase(parties_iter);
                    largest_party = (*max_element(parties.begin(), parties.end(), Party::compareParties));
                    return;               // Party was found, it's politicians were reassigned and the party was deleted
                }
            }
            throw InvalidName();          // Party Name was not found so InvalidName exception is thrown
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

/* Elections - each party does Primaries to elect chairman and than have elections between parties */
void PoliticalSys::elections() {
    if (parties.size() == 0 || politicians.size() == 0)
        return;
    
    vector<Party *>::iterator party_iter;
    cout << "----Primaries----\n";
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter)
        (*party_iter)->Primaries();

    cout << "----Elections----\n";
    Party *strongest_party = nullptr;
    int max_power = 0;
    int temp_power = 0;
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter) {
        temp_power = (*party_iter)->getPartyPower();
        if (temp_power > max_power) {
            max_power = temp_power;
            strongest_party = (*party_iter);
        }
    }
    cout << "----Elections Results----\n" << strongest_party->getName() << " party won the elections and ";
    if (strongest_party->getChairman() == nullptr)
        cout << "None";
    else
        cout << strongest_party->getChairman()->getPrivateName();
    cout << " is the prime minister" << endl;
}

/* Print politicans in the political system */
void PoliticalSys::printPoliticians() {
    vector<Politician *>::iterator pol_iter;
    cout << "----Politicians----\n";
    for (pol_iter = politicians.begin(); pol_iter != politicians.end(); ++pol_iter)
        (*pol_iter)->printPolitician();
}

/* Print parties in the political system */
void PoliticalSys::printParties() {
    vector<Party *>::iterator party_iter;
    cout << "----Parties----\n";
    for (party_iter = parties.begin(); party_iter != parties.end(); ++party_iter)
        (*party_iter)->printParty();
}

void PoliticalSys::BiggestParty() {
    if (parties.size() == 0)
        return;
    
    cout << "----Biggest Party----\n[";
    cout << largest_party->getName() << "," << largest_party->getPoliticians().size() << "]" << endl;
}

const vector<Politician*> &PoliticalSys::getPoliticians() const {
    return politicians;
}

const vector<Party*> &PoliticalSys::getParties() const {
    return parties;
}