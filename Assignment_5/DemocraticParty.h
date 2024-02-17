
#ifndef DEMOCRATICPARTY_H
#define DEMOCRATICPARTY_H

#include "Party.h"

// Inherent class from Party where only Democratic Politicians can join
class DemocraticParty: public Party {
public:
	// Constructor - requires party name
	DemocraticParty(char *name);
	// Destructor
	virtual ~DemocraticParty();

	// Add politician 
	virtual bool addPolitician(Politician* politician);

	// Print Democratic Party information
	virtual void printParty() const;
};


#endif // DEMOCRATICPARTY_H
