
#ifndef PARTY_H
#define PARTY_H

#include "Defs.h"
#include "Politician.h"

// Forward declartion of Politician class
class Politician;

// This generic Party class sets up basic Political party functions
// Adding politician should be implemented by inhereters to determine which politicians they allow into the party

class Party {
protected:
    char* name;
    Politician* chairman;
    vector<Politician*> politicians;
    // Notify observers on change in chairman
    void notifyPoliticians() const;

public:
    // Constructor - requires party name
    Party(char *name);

    // Destructor
    virtual ~Party();

    // Virtual add method to be overriden by specific add functions by specific parties
    virtual bool addPolitician(Politician* politician) = 0;
    
    // Remove politician from the party - will throw InvalidID exception if politician isn't found
    void removePolitician(const Politician& politician);

    // Perform Primarise and elect a chairman out of leader politicians in the party
    void Primaries();

    // Calculate the power of the party for elections
    int getPartyPower() const;
    
    // Return the number of politicians in the party
    int getPartySize() const;

    // Return the name of the party
    char* getName() const;

    // Return reference to the current chairman of the party
    const Politician* getChairman() const;

    // Returns vector of party politicians
    const vector<Politician*> &getPoliticians() const;

    // Print Politicians in the party - inhereters will print specific party information
    virtual void printParty() const;

    // static method which compares two parties using the operator<
    static bool compareParties(Party* party1, Party *party2);
};


#endif //PARTY_H
