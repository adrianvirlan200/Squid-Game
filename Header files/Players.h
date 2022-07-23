// class for players

#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class Players
{
protected:
    std::string first_name; // first name of player
    std::string last_name;  // last name of player
    std::string city;       // name of the city
    int debt;               // random number between 10000 and 100000
    int weight;             // random number between 50 and 100
    bool is_alive;          // 1 if he is still alive, otherwise 0

public:
    Players(std::string first_name, std::string last_name,
            std::string city, int debt, int weight) // constructor
    {
        this->first_name = first_name;
        this->last_name = last_name;
        this->city = city;
        this->debt = debt;
        this->weight = weight;
        this->is_alive = true;
    };

    ~Players() {} // destructor
    Players();    // default constructor

    virtual void print_all_data() = 0; // pure virtual function
    std::string getFirstName();        // getter
    std::string getLastName();         // getter
    std::string getCity();             // getter
    int getDebt();                     // getter
    int getWeight();                   // getter
    void setDebt(int);                 // setter
};