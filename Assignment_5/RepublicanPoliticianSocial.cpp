
#include "RepublicanPoliticianSocial.h"

// Politician Constructor - Republican Politician and Social Politician are virtual classes so constructor for Politician wont be called twice
RepublicanPoliticianSocial::RepublicanPoliticianSocial(char *privateName, char *surName, int id, int power): 
        RepublicanPolitician(privateName, surName, id, power), SocialPolitician(privateName, surName, id, power), Politician(privateName, surName, id, power) {}

// Politician Destructor
RepublicanPoliticianSocial::~RepublicanPoliticianSocial() {}

// Print RepublicanPoliticianLeader information
void RepublicanPoliticianSocial::printPolitician() const {
    RepublicanPolitician::printPolitician();
    Politician::printPolitician();
    SocialPolitician::printPolitician();
    char *chairman_name = (char*)"None";
    if (this->chairman != nullptr)
        chairman_name = this->chairman->getPrivateName();
    cout << "Chairman: " << chairman_name << endl;
}