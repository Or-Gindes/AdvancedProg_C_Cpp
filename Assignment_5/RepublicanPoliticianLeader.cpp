
#include "RepublicanPoliticianLeader.h"

// Politician Constructor - Republican Politician and Leader Politician are virtual classes so constructor for Politician wont be called twice
RepublicanPoliticianLeader::RepublicanPoliticianLeader(char *privateName, char *surName, int id, int power): 
        RepublicanPolitician(privateName, surName, id, power), LeaderPolitician(privateName, surName, id, power), Politician(privateName, surName, id, power) {}

// Politician Destructor
RepublicanPoliticianLeader::~RepublicanPoliticianLeader() {}

// Print RepublicanPoliticianLeader information
void RepublicanPoliticianLeader::printPolitician() const {
    RepublicanPolitician::printPolitician();
    Politician::printPolitician();
    LeaderPolitician::printPolitician();
    char *chairman_name = (char*)"None";
    if (this->chairman != nullptr)
        chairman_name = this->chairman->getPrivateName();
    cout << "Chairman: " << chairman_name << endl;
}