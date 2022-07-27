#include "../Header files/Aux.h"

int Aux::getSum()
{
    return this->sum;
}

// method add num to sum
void Aux::add(int num)
{
    sum += num;
}

void Aux::print() // for printing the team
{
    std::cout << "Team of supervisors with " << mask << " mask won the most money: " << sum << std::endl;
}