
#ifndef REPUBLICANPARTY_H
#define REPUBLICANPARTY_H

#include "Party.h"

// Inherent class from Party where only Republican Politicians can join
class RepublicanParty: public Party {
public:
	// Constructor - requires party name
	RepublicanParty(char *name);
	// Destructor
	virtual ~RepublicanParty();
    
	// Add politician 
	virtual bool addPolitician(Politician* politician);

	// Print Republican Party information
	virtual void printParty() const;
};


#endif // REPUBLICANPARTY_H
