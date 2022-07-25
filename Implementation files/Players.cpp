// implementation file for Players class

#include "../Header files/Players.h"

std::string Players::getFirstName()
{
    return this->first_name;
}
std::string Players::getLastName()
{
    return this->last_name;
}
std::string Players::getCity()
{
    return this->city;
}
int Players::getWeight()
{
    return this->weight;
}
void Players::setDebt(int val)
{
    this->debt = val;
}

int Players::getDebt()
{
    return this->debt;
}



