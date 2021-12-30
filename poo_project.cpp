#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>


class Players
{
protected:
    std::string first_name; // prenume
    std::string last_name;  // nume de familie
    std::string city;
    int debt;
    int weight;

public:
    Players(std::string first_name, std::string last_name, std::string city, int debt, int weight)
    {
        this->first_name = first_name;
        this->last_name;
        this->city = city;
        this->debt = debt;
        this->weight = weight;
    }
};

class Competitor : public Players
{
private:
    int number;

public:
};
class Supervisor : public Players
{
private:
    std::string mask_shape;

public:
};

int main()
{   
    Players *players[108];
    for(int i=0;i<99;i++)
    {
        players[0] = new Players();
    }



    std::default_random_engine generator;
    generator.seed(time(0));
    std::uniform_int_distribution<> dis(10000, 100000);
    return dis(generator);
    return 1;
}