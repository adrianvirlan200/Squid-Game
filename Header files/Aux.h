#include <iostream>

// aux class to store the amount of money every team of supervisors won
class Aux
{
private:
    int sum;             // stores the sum of money won
    std::string mask;    // stores the mask type of the team

public:
    Aux(std::string mask) // constructor sets sum to 0 and mask;
    {
        this->mask = mask;
        sum = 0;
    }

    ~Aux() {}           //default constructor 
    
    int getSum();       // getter returns the sum
    void add(int num);  // method add num to sum
    void print();       // for printing the team
};