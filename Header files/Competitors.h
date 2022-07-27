#pragma once
#include <iostream>
#include "Players.h"

class Competitors : public Players
{
private:
    int index = 0;                          // real index of competitor(1...99)
    static int number_of_competitors_alive; // static variable that stores the number of competitors(number of objects created in the beginning)  // 0...98
    std::string isSupervisedBy;             // stores the mask shape of supervisor mask shape allocated for current

public:
    Competitors(std::string first_name, std::string last_name, std::string city, int debt, int weight) : Players(first_name, last_name, city, debt, weight) // constructor
    {
        if (this->number_of_competitors_alive > 99) // more then 99 competitors
        {
            throw "Error: Too many competitors;\n"; // throw error
        }
        else // else increase the number of competitors by 1 and assign index to current competitor
        {
            number_of_competitors_alive++;
            this->index = number_of_competitors_alive;
        }
    }
    ~Competitors() {} // destructor

    void operator--();                           // overloading operator; kills player
    int getIndex_of_competitor();                // getter; returns the index of competitor
    static int getNumber_of_competitors_alive(); // getter that returns the number of competitors left alive
    void print_all_data();                       // overriding method to print all data for current competitor
    void setSupervisor(std::string);             // setter sets the supervisor for competitor
    void print_competitor_data_if_alive();       // method to print data if competitor is alive(is_alive == true)
    bool get_alive();                            // getter (returns is_alive)
    std::string get_his_supervisor();            // getter(returns the supervisor mask shape)

    friend void PRINT_ALL_COMPETITORS_ALIVE(Competitors *competitor[]);
};