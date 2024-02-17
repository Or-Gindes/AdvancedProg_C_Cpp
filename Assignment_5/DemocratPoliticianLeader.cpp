
#include "DemocratPoliticianLeader.h"

// Politician Constructor -Democratic Politician and Leader Politician are virtual classes so constructor for Politician wont be called twice
DemocratPoliticianLeader::DemocratPoliticianLeader(char *privateName, char *surName, int id, int power): 
        DemocratPolitician(privateName, surName, id, power), LeaderPolitician(privateName, surName, id, power), Politician(privateName, surName, id, power) {}

// Politician Destructor
DemocratPoliticianLeader::~DemocratPoliticianLeader() {}

// Print DemPoliticianLeader information
void DemocratPoliticianLeader::printPolitician() const {
    DemocratPolitician::printPolitician();
    Politician::printPolitician();
    LeaderPolitician::printPolitician();
    char *chairman_name = (char*)"None";
    if (this->chairman != nullptr)
        chairman_name = this->chairman->getPrivateName();
    cout << "Chairman: " << chairman_name << endl;
}
