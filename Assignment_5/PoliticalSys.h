#ifndef POLITICALSYS_H_
#define POLITICALSYS_H_

#include "RepublicanPoliticianLeader.h"
#include "RepublicanPoliticianSocial.h"
#include "DemocratPoliticianLeader.h"
#include "DemocratPoliticianSocial.h"
#include "RepublicanParty.h"
#include "DemocraticParty.h"

using namespace std;

/* This class handles the entire political system and interfaces with the menu operator */

class PoliticalSys
{
private:
    vector<Politician*> politicians;
    vector<Party*> parties;
    
    // Keep an updated pointer to the largest party
    Party* largest_party;
    // Support functions, creates the correct kind of politician, adds it to the system and lets it choose a party
    void addPolitician2Sys(char *firstName, char *surName, int ID, int power, char partyKind, char politicianKind);
    // Support function which creates a new political party, adds it to the system and allows politicians to joins it
    void addParty2Sys(char *name, char partyKind);
    // Support function which iterates over parties and lets the politican choose his home
    void findPartyForPolitician(Politician* politician);
    // Support function which iterates over politicans and lets them join the party
    void addPolitician2Party(Party* party);

public:

    // Constructor for the political system using a configuration file. Also acts a default constructor with no file
    PoliticalSys(char *configFilePath=NULL);    // throw(InvalidInput);

    // Destructor - will free memory allocated to each politician and each party created in the political system
    ~PoliticalSys();

    // Request input from user to add new politicians into the system
    void addPolitician();                       // throw(InvalidID, InvalidInput); this type of declation raises "dynamic exception specifications are not permitted in this mode" error in compilation

    // Add a new party to the political system
    void addParty();                            // throw(InvalidName, InvalidInput)

    // Remove a politician from the politician system
    void removePolitician();                    // throw(InvalidID);

    // Remove a party from the politician system, allowing its politicians to find a new party for themselves
    void removeParty();                         // throw(InvalidName)

    // Perform elections in the political system which include primaries and general elections where parties compare their total power
    void elections();

    // Print politicans in the political system
    void printPoliticians();

    // Print parties in the political system
    void printParties();

    // Print the biggest party
    void BiggestParty();

    const vector<Politician*> &getPoliticians() const;

    const vector<Party*> &getParties() const;
};

#endif /* POLITICALSYS_H_ */