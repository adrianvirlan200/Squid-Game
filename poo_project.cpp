#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>

class Players
{
public:                     // protected
    std::string first_name; // prenume
    std::string last_name;  // nume de familie
    std::string city;
    int debt;   // random between 10000 and 100000
    int weight; // random between 50 and 100

public:
    Players(std::string first_name, std::string last_name, std::string city, int debt, int weight)
    {
        this->first_name = first_name;
        this->last_name = last_name;
        this->city = city;
        this->debt = debt;
        this->weight = weight;
    }
/*
    void getFirstName();
    void getLastName();
    void getCity();
    void getDebt();
    void getWeight();
*/
};

class Competitors : public Players
{
public: // private
    int index = 0;
    static int number_of_competitors_alive; // static variable

//public:
    Competitors(std::string first_name, std::string last_name, std::string city, int debt, int weight) : Players(first_name, last_name, city, debt, weight)
    {
        number_of_competitors_alive++;
        this->index = number_of_competitors_alive;
    }

    static void decrease_number_of_competitors_alive(int); // static method use to decrease the number of competitors alive by num
    int getIndex_of_competitor();                          // getter; returns the index of competitor
    static int getNumber_of_competitors_alive();           // getter that returns the number of competitor left alive
    void print_all_data();
};

int Competitors::number_of_competitors_alive = 0;

void Competitors::decrease_number_of_competitors_alive(int num)
{
    if (number_of_competitors_alive <= 0)
    {
        throw "Error: no competitor is left alive\n";
    }
    else if (number_of_competitors_alive < num)
    {
        throw "Error: number of competitors eliminated is greter then competitors left alive\n";
    }
    else
    {
        number_of_competitors_alive -= num;
    }
}

int Competitors::getIndex_of_competitor()
{
    return this->index;
}

int Competitors::getNumber_of_competitors_alive()
{
    return number_of_competitors_alive;
}

void Competitors::print_all_data()
{
    std::cout << this->first_name << " " << this->last_name << " " << this->index << " " << this->city << " " << this->debt << " " << this->weight << std::endl;
}

class Supervisors : public Players
{
public: // private
    std::string mask_shape;
    static int number_of_supervisors;

public:
    Supervisors(std::string first_name, std::string last_name, std::string city, int debt, int weight, std::string mask_shape) : Players(first_name, last_name, city, debt, weight)
    {
        number_of_supervisors++;
        this->mask_shape = mask_shape;
    }

    std::string getMask_shape();
    static int getNumber_of_supervisors();
    void print_all_data();
};

int Supervisors::number_of_supervisors = 0;

std::string Supervisors::getMask_shape()
{
    return this->mask_shape;
}

int Supervisors::getNumber_of_supervisors()
{
    return number_of_supervisors;
}

void Supervisors::print_all_data()
{
    std::cout << this->first_name << " " << this->last_name << " " << this->mask_shape << " " << this->city << " " << this->debt << " " << this->weight << std::endl;
}

// main function
int main()
{
    Competitors *competitor[99]; // array of pointers type Competitors, max 99 elements;
    Supervisors *supervisor[9];  // array of pointers type Supervisors, max 9 elements;

    int curent_number_of_supervisors = 0; // max 8
    int curent_number_of_competitors = 0; // max 98

    // for generating random large numbers between 10000 and 100000
    std::random_device rd;                                          // seed
    std::default_random_engine generator(rd());                     // random number generator
    std::uniform_int_distribution<int> distribution(10000, 100000); // random between 10000 and 100000
    // std::cout<<distribution(generator)<<std::endl;

    // for generating random numbers smaller than RAND_MAX(~32767)
    srand(time(NULL)); // seed
    // rand() % 101;

    // variable used for supervisors masks
    int num_of_supervisors_with_circle_mask = 0;    // max3
    int num_of_supervisors_with_triangle_mask = 0;  // max3
    int num_of_supervisors_with_rectangle_mask = 0; // max3

    int c = 0;
    ;

    for (int i = 0; i < 108; i++) // alocating memory for every player;
    {
        // random

        // if the number between 0-25 generated random is devided by 5 =>that player is a supervisor,else it is a competitor
        // repeat the proces for every player until all slots are taken
        // genearte random number;
        if ((rand() % 26) % 5 == 0) // it's a supervisor
        {
            if (curent_number_of_supervisors < 9) // there are free supervisor slots
            {
                switch (rand() % 3 + 1) // random number beteen 1 and 3
                {
                case 1: // cicle mask
                    if (num_of_supervisors_with_circle_mask < 3)
                    {
                        c++;
                        num_of_supervisors_with_circle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "circle");
                    }
                    break;
                case 2: // rectangle mask
                    if (num_of_supervisors_with_rectangle_mask < 3)
                    {
                        c++;
                        num_of_supervisors_with_rectangle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "rectangle");
                    }
                    break;
                case 3: // triangle
                    if (num_of_supervisors_with_triangle_mask < 3)
                    {
                        c++;
                        num_of_supervisors_with_triangle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "triangle");
                    }
                    break;
                }

                if (c == 0) // if one of 3 slots is full
                {
                    if (num_of_supervisors_with_circle_mask < 3) // add circle mask if free
                    {
                        num_of_supervisors_with_circle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "circle");
                    }
                    else if (num_of_supervisors_with_rectangle_mask < 3) // add rectangle mask if free
                    {
                        num_of_supervisors_with_rectangle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "rectangle");
                    }
                    else if (num_of_supervisors_with_triangle_mask < 3) // add triangle mask if free
                    {
                        num_of_supervisors_with_triangle_mask++;
                        supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "triangle");
                    }
                }
                else // reset c
                {
                    c = 0;
                }
            }
            else // else all slots are occupied, add curent user as an competitor
            {
                competitor[curent_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50);
            }
        }
        else // it's a competitor
        {
            if (curent_number_of_competitors < 99) // if there are free slot, add curent user as a competitor
            {
                competitor[curent_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50);
            }
            else if (num_of_supervisors_with_circle_mask < 3) // if there are not free slots available, add curent competitor as an supervisor(repeat the process of adding a supervisor)
            {
                num_of_supervisors_with_circle_mask++;
                supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "circle");
            }
            else if (num_of_supervisors_with_rectangle_mask < 3)
            {
                num_of_supervisors_with_rectangle_mask++;
                supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "rectangle");
            }
            else if (num_of_supervisors_with_triangle_mask < 3)
            {
                num_of_supervisors_with_triangle_mask++;
                supervisor[curent_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", distribution(generator), rand() % 51 + 50, "triangle");
            }
        }
    }

    std::cout << "Competitors:\n";
    for (int i = 0; i < 99; i++)
    {
        competitor[i]->print_all_data();
    }

    std::cout << "Supervisors:\n";
    for (int i = 0; i < 9; i++)
    {
        supervisor[i]->print_all_data();
    }

    std::cout<<"\n-->\n"<<competitor[0]->index;

    // free memory
    for (int i = 0; i < 99; i++)
    {
        delete competitor[i];
    }

    for (int i = 0; i < 9; i++)
    {
        delete supervisor[i];
    }

    return 1;
}