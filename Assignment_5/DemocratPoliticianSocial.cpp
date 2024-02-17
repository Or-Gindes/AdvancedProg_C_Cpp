
#include "DemocratPoliticianSocial.h"

// Politician Constructor -Democratic Politician and Social Politician are virtual classes so constructor for Politician wont be called twice
DemocratPoliticianSocial::DemocratPoliticianSocial(char *privateName, char *surName, int id, int power): 
        DemocratPolitician(privateName, surName, id, power), SocialPolitician(privateName, surName, id, power), Politician(privateName, surName, id, power) {}

// Politician Destructor
DemocratPoliticianSocial::~DemocratPoliticianSocial() {}

// Print DemPoliticianSocial information
void DemocratPoliticianSocial::printPolitician() const {
    DemocratPolitician::printPolitician();
    Politician::printPolitician();
    SocialPolitician::printPolitician();
    char *chairman_name = (char*)"None";
    if (this->chairman != nullptr)
        chairman_name = this->chairman->getPrivateName();
    cout << "Chairman: " << chairman_name << endl;
}
