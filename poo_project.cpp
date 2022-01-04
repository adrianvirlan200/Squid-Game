#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip> // std::setw

// template function for generating random numbers between 2 values
template <class T>
T generate_random(int min, int max)
{
    // rand() is generating random numbers smaller than RAND_MAX(~32767),
    return (std::rand() * std::rand()) % (max - min + 1) + min;
}

class Players
{
public:                     // protected
    std::string first_name; // prenume
    std::string last_name;  // nume de familie
    std::string city;
    int debt;   // random between 10000 and 100000
    int weight; // random between 50 and 100
    bool is_alive;

public:
    Players(std::string first_name, std::string last_name, std::string city, int debt, int weight) // constructor
    {
        this->first_name = first_name;
        this->last_name = last_name;
        this->city = city;
        this->debt = debt;
        this->weight = weight;
        this->is_alive = true;
    }
    ~Players() {} // destructor

    virtual void print_all_data() = 0; // pure virtual function

    void getFirstName();
    void getLastName();
    void getCity();
    void getDebt();
    void getWeight();
};

class Competitors : public Players
{
public:                                     // private
    int index = 0;                          // index of competitor
    static int number_of_competitors_alive; // static variable that stores the number of competitors(number of objects created)
    std::string isSupervisedBy;             // stores the supervisor allocated for current

    // public:
    Competitors(std::string first_name, std::string last_name, std::string city, int debt, int weight) : Players(first_name, last_name, city, debt, weight) //
    {
        if (number_of_competitors_alive > 99)
        {
            throw "Error: Too many competitors;\n";
        }
        else
        {
            number_of_competitors_alive++;
        }
        this->index = number_of_competitors_alive;
    }
    ~Competitors() {} // destructor

    void operator--();                           // overloading operator; kills player
    int getIndex_of_competitor();                // getter; returns the index of competitor
    static int getNumber_of_competitors_alive(); // getter that returns the number of competitor left alive
    void print_all_data();                       // overriding
    void setSupervisor(std::string);             // setter
    void print_competitor_data_if_alive();
};

int Competitors::number_of_competitors_alive = 0;

void Competitors::operator--() // overloading -- operator;eliminate current competitor
{
    if (number_of_competitors_alive < 1)
    {
        throw "Error: 0 competitors alive;\n"; // throw exception
    }
    else if (this->is_alive == false)
    {
        throw "Error: Competitor already eliminated;\n"; // throw exception
    }
    else
    {
        this->is_alive = false;
        number_of_competitors_alive--;
    }
}

void Competitors::setSupervisor(std::string mask_type)
{
    this->isSupervisedBy = mask_type;
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
    std::cout << this->first_name << std::setw(15) << this->last_name << std::setw(15) << this->index << std::setw(15) << this->city << std::setw(15) << this->debt << std::setw(15) << this->weight << std::endl;
}

void Competitors::print_competitor_data_if_alive()
{
    if (this->is_alive == true)
    {
        std::cout << this->first_name << std::setw(15) << this->last_name << std::setw(15) << this->city << std::setw(15) << this->debt << std::setw(15) << this->weight << std::endl;
    }
}
class Supervisors : public Players
{
public: // private
    std::string mask_shape;
    static int total_number_of_supervisors;
    static int num_of_supervisors_with_circle_mask;    // max3
    static int num_of_supervisors_with_triangle_mask;  // max3
    static int num_of_supervisors_with_rectangle_mask; // max3
    int isSupervising[11];                             // every supervisor has 11 competitors
    int num = 0;                                       // index for competitor vector
public:
    Supervisors(std::string first_name, std::string last_name, std::string city, int debt, int weight, std::string mask_shape) : Players(first_name, last_name, city, debt, weight)
    {
        total_number_of_supervisors++;
        this->mask_shape = mask_shape;

        if (this->mask_shape == "circle")
        {
            if (num_of_supervisors_with_circle_mask >= 3)
            {
                throw "Too many supervisors with circle masks;\n";
            }
            else
            {
                num_of_supervisors_with_circle_mask++;
            }
        }
        else if (this->mask_shape == "rectangle")
        {
            if (num_of_supervisors_with_rectangle_mask >= 3)
            {
                throw "Too many supervisors with rectangle masks;\n";
            }
            else
            {
                num_of_supervisors_with_rectangle_mask++;
            }
        }
        else if (this->mask_shape == "triangle")
        {
            if (num_of_supervisors_with_triangle_mask >= 3)
            {
                throw "Too many supervisors with triangle masks;\n";
            }
            else
            {
                num_of_supervisors_with_triangle_mask++;
            }
        }
    }

    std::string getMask_shape();
    static int getNumber_of_supervisors();
    void print_all_data();                                   // overriding
    static int get_num_of_supervisors_with_circle_mask();    // static getters
    static int get_num_of_supervisors_with_triangle_mask();  // static getters
    static int get_num_of_supervisors_with_rectangle_mask(); // static getters
};

int Supervisors::total_number_of_supervisors = 0;
int Supervisors::num_of_supervisors_with_circle_mask = 0;
int Supervisors::num_of_supervisors_with_triangle_mask = 0;
int Supervisors::num_of_supervisors_with_rectangle_mask = 0;

std::string Supervisors::getMask_shape()
{
    return this->mask_shape;
}

int Supervisors::getNumber_of_supervisors()
{
    return total_number_of_supervisors;
}
int Supervisors::get_num_of_supervisors_with_circle_mask()
{
    return num_of_supervisors_with_circle_mask;
}
int Supervisors::get_num_of_supervisors_with_triangle_mask()
{
    return num_of_supervisors_with_triangle_mask;
}
int Supervisors::get_num_of_supervisors_with_rectangle_mask()
{
    return num_of_supervisors_with_rectangle_mask;
}

void Supervisors::print_all_data()
{
    std::cout << this->first_name << std::setw(15) << this->last_name << std::setw(15) << this->mask_shape << std::setw(15) << this->city << std::setw(15) << this->debt << std::setw(15) << this->weight << std::endl;
}

// main function
int main()
{
    Competitors *competitor[99]; // array of pointers type Competitors, max 99 elements;
    Supervisors *supervisor[9];  // array of pointers type Supervisors, max 9 elements;

    int current_number_of_supervisors = 0; // max 8
    int current_number_of_competitors = 0; // max 98

    srand(time(NULL)); // generate the seed for random numbers

    bool c = 0;

    for (int i = 0; i < 108; i++) // dynamically allocating memory for every player;
    {
        // if the number between 0-25 generated random is divided by 5 =>that player is a supervisor,else it is a competitor
        // repeat the process for every player until all slots are taken
        // if one class of supervisors is full, then just search for another free slot in
        // if no slot is avaible, then that player is a competitor

        // genearte random number;
        if (generate_random<int>(0, 25) % 5 == 0) // it's a supervisor
        {
            if (current_number_of_supervisors < 9) // there are free supervisor slots
            {
                switch (generate_random<int>(1, 3) % 3) // random number beteen 1 and 3
                {
                case 0: // circle mask
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3)
                    {
                        c++;
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    break;
                case 1: // rectangle mask
                    if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3)
                    {
                        c++;
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    break;
                case 2: // triangle
                    if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3)
                    {
                        c++;
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                    break;
                }
                if (c == 0) // if one of 3 slots is full
                {
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // add circle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3) // add rectangle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3) // add triangle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                }
                else // we added a supervisor, reset c
                {
                    c = 0;
                }
            }
            else // else all slots are occupied, add current user as an competitor
            {
                competitor[current_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
        }
        else // it's a competitor
        {
            if (current_number_of_competitors < 99) // if there are free slot, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
            else if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // if there are not free slots available, add current competitor as an supervisor(repeat the process of adding a supervisor)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
            }
            else if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
            }
            else if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
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

    int count = 0;
    for (int i = 0; i < 9; i++) // 9 supervisors
    {
        for (int j = 0; j < 11; j++) // each supervisor has 11 competitors to supervise
        {
            supervisor[i]->isSupervising[supervisor[i]->num++] = count++;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        std::cout << "Supervisor " << i + 1 << " with " << supervisor[i]->getMask_shape() << " mask is supervising competitor no.:" << std::setw(10);
        for (int j = 0; j < 11; j++)
        {
            std::cout << supervisor[i]->isSupervising[j] << " ";
        }
        std::cout << std::endl;
    }

    int i = 0;
    int breakk = 0;
    while (i < 99) // 99 competitors
    {
        breakk = 0;
        for (int j = 0; j < 9 && breakk == 0; j++) // 9 supervisors
        {
            for (int k = 0; k < 11 && breakk == 0; k++)
            {
                if (supervisor[j]->isSupervising[k] == competitor[i]->getIndex_of_competitor() - 1) // getIndex_of_competitor returns the number of competitor + 1;
                {
                    competitor[i]->setSupervisor(supervisor[j]->getMask_shape());
                    i++;
                    breakk = 1;
                }
            }
        }
    }

    for (int i = 0; i < 99; i++)
    {
        std::cout << "Competitor no. " << i << " is supervised by a supervisor with " << competitor[i]->isSupervisedBy << " mask" << std::endl;
    }

    // free memory
    for (int i = 0; i < 99; i++)
    {
        delete competitor[i];

        if (i < 9)
        {
            delete supervisor[i];
        }
    }

    return 1;
}