#include <iostream>
//#include <stdlib.h>
#include <time.h>
//#include <math.h>
//#include <iomanip> // std::setw
#include <vector>
// template function that generate random numbers between 2 values
template <class T>
T generate_random(int min, int max)
{
    // rand() is generating random numbers smaller than RAND_MAX(~32767),
    return (std::rand() * std::rand()) % (max - min + 1) + min;
}

// class for players
class Players
{
protected:
    std::string first_name;
    std::string last_name;
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
    ~Players() {}                      // destructor
    Players();                         // defauld constructor
    virtual void print_all_data() = 0; // pure virtual function

    std::string getFirstName(); // getters
    std::string getLastName();
    std::string getCity();
    int getDebt();
    int getWeight();
    void setDebt(int); // setter for debt
};
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

// class for competitors
class Competitors : public Players
{
private:
    int index = 0;                          // real index of competitor(1...99)
    static int number_of_competitors_alive; // static variable that stores the number of competitors(number of objects created in the begining)
                                            // 0...98
    std::string isSupervisedBy;             // stores the mask shape of supervisor mask shape allocated for current

public:
    Competitors(std::string first_name, std::string last_name, std::string city, int debt, int weight) : Players(first_name, last_name, city, debt, weight) // constructor
    {
        if (number_of_competitors_alive > 99) // more then 99 competitors
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

    friend void PRINT_ALL_COMPETITORS(Competitors); // friend functions
    friend void PRINT_ALL_COMPETITORS_ALIVE(Competitors);
};

int Competitors::number_of_competitors_alive = 0;

bool Competitors::get_alive()
{
    return this->is_alive;
}

std::string Competitors::get_his_supervisor()
{
    return this->isSupervisedBy;
}

void Competitors::operator--() // overloading -- operator; eliminate current competitor
{
    // check if there are competitors alive left and if current competitor is alive
    if (number_of_competitors_alive < 1) // min 1 player
    {
        throw "Error: 0 competitors alive;\n"; // throw exception
    }
    else if (this->is_alive == false)
    {
        throw "Error: Competitor already eliminated;\n"; // throw exception
    }
    else
    {
        this->is_alive = false;        // eliminate competitor
        number_of_competitors_alive--; // reduce by 1 the total number of competitors alive
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

// aux method to print all data on coloms (the space between coloms is the same, although the names have diffrent sizes)
void space(std::string &string, int n)
{
    int initial_length = string.length(); // save the initial length of the string, because we will modify the length every iteration
    for (int i = initial_length; i < n * 15; i++)
    {
        string.append(" ");
    }
}
// print all data on coloms
void Competitors::print_all_data()
{
    std::string print;
    int i = 1;

    print.append(this->first_name);
    space(print, i++);
    print.append(this->last_name);
    space(print, i++);
    print.append(std::to_string(this->index));
    space(print, i++);
    print.append(this->city);
    space(print, i++);
    print.append(std::to_string(this->debt));
    space(print, i++);
    print.append(std::to_string(this->weight));

    std::cout << print << std::endl;
}

void Competitors::print_competitor_data_if_alive()
{
    if (this->is_alive == true)
    {
        this->print_all_data();
    }
}

// class for supervisor
class Supervisors : public Players
{
private:
    std::string mask_shape; // type of mask
    // static variables that stores the total number of supervisors and the num of supervisors with every type of mask
    static int total_number_of_supervisors;            // 0...8
    static int num_of_supervisors_with_circle_mask;    // 0,1,2
    static int num_of_supervisors_with_triangle_mask;  // 0,1,2
    static int num_of_supervisors_with_rectangle_mask; // 0,1,2
public:
    std::vector<int> isSupervising; // vector that stores the index of every competitor that is supervised by current supervisor
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

    ~Supervisors() {}
    Supervisors();                                 // defaut constructor
    Supervisors(const Supervisors &old_supervisor) // copy constructor
    {
        this->first_name = old_supervisor.first_name;
        this->last_name = old_supervisor.last_name;
        this->city = old_supervisor.city;
        this->debt = old_supervisor.debt;
        this->weight = old_supervisor.weight;
        this->is_alive = old_supervisor.is_alive;
        this->mask_shape = old_supervisor.mask_shape;
        this->total_number_of_supervisors = old_supervisor.total_number_of_supervisors;
        this->num_of_supervisors_with_circle_mask = old_supervisor.num_of_supervisors_with_circle_mask;
        this->num_of_supervisors_with_triangle_mask = old_supervisor.num_of_supervisors_with_triangle_mask;
        this->num_of_supervisors_with_rectangle_mask = old_supervisor.num_of_supervisors_with_rectangle_mask;
        this->isSupervising = old_supervisor.isSupervising;
    }

    // methods
    std::string getMask_shape();
    static int getNumber_of_supervisors();
    static int get_num_of_supervisors_with_circle_mask();    // static getters
    static int get_num_of_supervisors_with_triangle_mask();  // static getters
    static int get_num_of_supervisors_with_rectangle_mask(); // static getters
    void print_all_data();                                   // overriding

    friend void PRINT_ALL_SUPERVISORS(Supervisors);
    friend void SORT_SUPERVISORS(Supervisors);
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

// method to print current supervisor data(similar to print_all_data of competitor)
void Supervisors::print_all_data()
{
    std::string print;
    int i = 1;

    print.append(this->first_name);
    space(print, i++);
    print.append(this->last_name);
    space(print, i++);
    print.append(this->mask_shape);
    space(print, i++);
    print.append(this->city);
    space(print, i++);
    print.append(std::to_string(this->debt));
    space(print, i++);
    print.append(std::to_string(this->weight));

    std::cout << print << std::endl;
}

// FUNCTIONS
// function used to print all supervisors
void PRINT_ALL_SUPERVISORS(Supervisors *supervisor[])
{
    std::cout << "\nAll supervisors:\n";
    std::cout << "First Name     Last Name      Mask Shape     City           Debt           Weight" << std::endl;
    std::cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < 9; i++)
    {
        supervisor[i]->print_all_data();
    }
}

void SORT_SUPERVISORS(Supervisors *supervisor[])
{
    Supervisors *aux_supervisor;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (supervisor[i]->getDebt() > supervisor[j]->getDebt())
            {
                aux_supervisor = supervisor[i];
                supervisor[i] = supervisor[j];
                supervisor[j] = aux_supervisor;
            }
        }
    }
}

// function used to print all competitors
void PRINT_ALL_COMPETITORS(Competitors *competitor[])
{
    std::cout << "\nAll competitors:\n";
    std::cout << "First Name     Last Name      Index          City           Debt           Weight" << std::endl;
    std::cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < 99; i++)
    {
        competitor[i]->print_all_data();
    }
}
// function used to print all competitors that are not eliminated
void PRINT_ALL_COMPETITORS_ALIVE(Competitors *competitor[])
{
    std::cout << "\nAll competitors Alive:\n";
    std::cout << "First Name     Last Name      Index          City           Debt           Weight" << std::endl;
    std::cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < 99; i++)
    {
        competitor[i]->print_competitor_data_if_alive();
    }
}
// red light green light game
void RED_LIGHT_GREEN_LIGHT(Competitors *competitor[])
{
    std::cout << "\nRED LIGHT GREEN LIGHT BEGINS!\n";
    for (int i = 1; i < 99; i += 2) // index of array = real_index_of_player -1
    {
        --(*competitor[i]); // eliminate the competitor
    }
}
// aux function of TUG_OF_WAR game, used to eliminate a team
void ELIMINATE_TEAM(Competitors **team[])
{
    // eliminate every player of the team
    for (int i = 0; i < 12; i++)
    {
        if ((*team[i])->get_alive() == false) // check if player of the team is eliminated->if yes this means that that team is already eliminated or another error
        {
            throw "Team/player already eliminated or other error;\n"; // throw an error;
        }
        else
        {
            --(**team[i]); // eliminate all competitors of that team
        }
    }
}
// TUG OF WAR GAME
void TUG_OF_WAR(Competitors **team[][12])
{

    int sum[4] = {0}; // sum[i] = total weight of team[i]
    // calculate the total weight for every team
    for (int i = 0; i < 12; i++)
    {
        sum[0] += (*team[0][i])->getWeight();
        sum[1] += (*team[1][i])->getWeight();
        sum[2] += (*team[2][i])->getWeight();
        sum[3] += (*team[3][i])->getWeight();
    }

    std::cout << "\nTUG OF WAR BEGINS!\n";

    // print all teams
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Team" << i + 1 << " [total weight: " << sum[i] << "]:\n";
        for (int j = 0; j < 12; j++)
        {
            (*team[i][j])->print_competitor_data_if_alive();
        }
    }

    int team_already_eliminated[4] = {0}; // use to check if a team is already eliminated

    // 2 for to generate all possible combinations
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (sum[i] < sum[j] && team_already_eliminated[i] == 0) // team 1 in not already eliminated
            {
                try
                {
                    ELIMINATE_TEAM(team[i]);        // eliminate team with lower weight
                    team_already_eliminated[i] = 1; // set team as eliminated
                }
                catch (const char *msg)
                {
                    std::cout << msg;
                    return;
                }
            }
            else if (sum[j] < sum[i] && team_already_eliminated[j] == 0) // team2 not already eliminated
            {
                try
                {
                    ELIMINATE_TEAM(team[j]);
                    team_already_eliminated[j] = 1; // set team as eliminated
                }
                catch (const char *msg)
                {
                    std::cout << msg;
                    return;
                }
            }
        }
    }
}
// marbles game
void MARBLES(Competitors *competitor1, int rand_num_1, Competitors *competitor2, int rand_num_2)
{
    if (competitor1->get_alive() == false || competitor2->get_alive() == false)
    {
        throw "One competitor already eliminated;";
    }
    // competitor with bigger number is eliminated
    if (rand_num_1 > rand_num_2)
    {
        // print competitor index and his choice
        std::cout << "Competitor with index " << competitor1->getIndex_of_competitor() << " got: " << rand_num_1 << "   X" << std ::endl;
        std::cout << "Competitor with index " << competitor2->getIndex_of_competitor() << " got: " << rand_num_2 << std ::endl;
        std::cout << "-------\n";
        --(*competitor1); // eliminate 1
    }
    else if (rand_num_2 > rand_num_1)
    {
        // print competitor index and his choice
        std::cout << "Competitor with index " << competitor1->getIndex_of_competitor() << " got: " << rand_num_1 << std ::endl;
        std::cout << "Competitor with index " << competitor2->getIndex_of_competitor() << " got: " << rand_num_2 << "   X" << std ::endl;
        std::cout << "-------\n";
        --(*competitor2); // eliminate 2
    }
}
// aux function used  for GENKEN game
std::string GENKEN_AUX(int num)
{
    // converts the number to its equivalent
    switch (num)
    {
    case 1:
        return "rock";
        break;
    case 2:
        return "paper";
        break;
    case 3:
        return "scissors";
        break;
    default:
        throw "Invalid number;\n";
    }
}
// GENKEN game
//  function returns 0 if no competitor was eliminated
int GENKEN(Competitors *competitor1, int num_1, Competitors *competitor2, int num_2)
{
    // rock = 1;
    // paper = 2;
    // scissor = 3;

    switch (num_1 - num_2)
    {
    // both chose the same number
    case 0:
        std::cout << "Competitor with index: " << competitor1->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_1) << std::endl;
        std::cout << "Competitor with index: " << competitor2->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_2) << std::endl;
        std::cout << "-----------\n";
        return 0; // none is eliminated
        break;
    // 1 = paper(2) && 2 = rock(1) => 2 eliminated   2-1(case 1:)
    // or 1 = scissors(3) && 2 = paper(2) => 2 eliminated  3-2(case 1:)
    // or 1 = rock(1) && 2 = scissors(3) => 2 eliminated 1-3(case -2:)
    case 1:
    case -2:
        std::cout << "Competitor with index: " << competitor1->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_1) << std::endl;
        std::cout << "Competitor with index: " << competitor2->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_2) << "   X" << std::endl;
        std::cout << "-----------\n";
        --(*competitor2); // in all 3 cases competitor 2 is eliminated;
        break;
    // 1 = scissors(3) && 2 = rock(1) => 1 eliminated 3-1(case 2:)
    // 1 = rock(1) && 2 = paper(2) => 1 eliminated 1-2(case -1:)
    // 1 = paper(2) && 2 = scissors(3) => 1 eliminated 2-3(case -1:)
    case 2:
    case -1:
        std::cout << "Competitor with index: " << competitor1->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_1) << "   X" << std::endl;
        std::cout << "Competitor with index: " << competitor2->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_2) << std::endl;
        std::cout << "-----------\n";
        --(*competitor1); // in all 3 cases competitor1 is eliminated;
        break;
    default:
        throw "Invalid numbers;\n";
    }

    return 1; // 1 competitor was eliminated
}

// aux class to store the amount of money every team of supervisors won
class Aux
{
private:
    int sum;          // stores the sum of money won
    std::string mask; // stores the mask type of the team

public:
    Aux(std::string mask) // default constructor sets sum to 0 and mask;
    {
        this->mask = mask;
        sum = 0;
    }

    ~Aux() {}

    // getter returns the sum
    int getSum()
    {
        return this->sum;
    }

    // method add num to sum
    void add(int num)
    {
        sum += num;
    }

    void print() // for printing the team
    {
        std::cout << "Team of supervisors with " << mask << " mask won the most money: " << sum << std::endl;
    }
};

// main function
int main()
{
    Competitors *competitor[99]; // array of pointers type Competitors, max 99 elements;
    Supervisors *supervisor[9];  // array of pointers type Supervisors, max 9 elements;

    int current_number_of_supervisors = 0; // max 8
    int current_number_of_competitors = 0; // max 98

    srand(time(NULL)); // generate the seed for rand() (used to generete random numbers)

    int assigned = 0;
    for (int i = 0; i < 108; i++) // dynamically allocating memory for every player;
    {

        // get data for all players
        // randomly generate names
        std::string first_name, last_name, city;
        int max_Fname, max_Lname, max_city;
        max_Fname = generate_random<int>(3, 10); // every name has: min 3 letters, max 10
        max_Lname = generate_random<int>(3, 10);
        max_city = generate_random<int>(3, 10);

        first_name.push_back(generate_random<char>(65, 90)); // first letter is capital letter
        last_name.push_back(generate_random<char>(65, 90));  // first letter is capital letter
        city.push_back(generate_random<char>(65, 90));       // first letter is capital letter

        // lower cases
        for (int i = 1; i < max_Fname; i++)
        {
            first_name.push_back(generate_random<char>(97, 122));
        }

        for (int i = 1; i < max_Lname; i++)
        {
            last_name.push_back(generate_random<char>(97, 122));
        }
        for (int i = 1; i < max_city; i++)
        {
            city.push_back(generate_random<char>(97, 122));
        }

        // if the number between 0-25 generated random is divided by 5 =>that player is a supervisor,else it is a competitor
        // repeat the process for every player until all slots are taken

        // if one class of supervisors is full, then just search for another free slot in others classes
        // if no slot is available, then that player is a competitor

        // if no slots for competitor is available, then that player is a supervisor

        // generate random number;
        if (generate_random<int>(0, 25) % 5 == 0) // it's a supervisor
        {
            if (current_number_of_supervisors < 9) // there are free supervisor slots
            {
                switch (generate_random<int>(1, 3) % 3) // random number between 1 and 3 to chose the type of mask
                {
                case 0: // circle mask
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3)
                    {
                        assigned++;
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    break;
                case 1: // rectangle mask
                    if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3)
                    {
                        assigned++;
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    break;
                case 2: // triangle
                    if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3)
                    {
                        assigned++;
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                    break;
                }
                if (assigned == 0) // if one of 3 slots is full we search for a free slot in other classes of supervisors
                {
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // add circle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3) // add rectangle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3) // add triangle mask if free
                    {
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                }
                else // we added a supervisor, reset assigned for the next supervisor
                {
                    assigned = 0;
                }
            }
            else // else all slots for supervisors are occupied, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
        }
        else // it's a competitor
        {
            if (current_number_of_competitors < 99) // if there are free slots for competitors, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
            else if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // if there are not free slots available, add current player as a supervisor(repeat the process of adding a supervisor)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
            }
            else if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
            }
            else if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3)
            {
                supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
            }
        }

        // reset the strings for the next competitors
        first_name.clear();
        last_name.clear();
        city.clear();
    }

    PRINT_ALL_COMPETITORS(competitor);
    PRINT_ALL_SUPERVISORS(supervisor);

    int count = 0;

    for (int i = 0; i < 9; i++) // 9 supervisors
    {
        for (int j = 0; j < 11; j++) // each supervisor has 11 competitors to supervise
        {
            supervisor[i]->isSupervising.push_back(count++);
        }
    }

    std::cout << std::endl;

    // print what competitors are allocated for every supervisor
    for (int i = 0; i < 9; i++)
    {
        std::cout << "Supervisor " << i + 1 << " with " << supervisor[i]->getMask_shape() << " mask is supervising competitor no.:"
                  << "\t";
        for (std::vector<int>::iterator it = supervisor[i]->isSupervising.begin(); it != supervisor[i]->isSupervising.end(); it++)
        {
            std::cout << *it + 1 << " ";
        }
        std::cout << std::endl;
    }

    // search what supervisor is supervising each competitor
    int i = 0;
    int breakk = 0; // breakk == 0 => didn't find competitor's i supervisor

    while (i < 99) // 99 competitors
    {
        breakk = 0;                                // reset
        for (int j = 0; j < 9 && breakk == 0; j++) // 9 supervisors
        {
            for (std::vector<int>::iterator it = supervisor[j]->isSupervising.begin(); it != supervisor[j]->isSupervising.end() && breakk == 0; it++)
            {
                if (*it == competitor[i]->getIndex_of_competitor() - 1) // getIndex_of_competitor returns the number of competitor + 1;
                {
                    competitor[i]->setSupervisor(supervisor[j]->getMask_shape());
                    i++;        // go to the next competitor
                    breakk = 1; // set as found
                }
            }
        }
    }

    std::cout << std::endl;

    // print supervisor for every competitor
    for (int i = 0; i < 99; i++)
    {
        std::cout << "Competitor no. " << i + 1 << " is supervised by a supervisor with " << competitor[i]->get_his_supervisor() << " mask" << std::endl;
    }

    // first game
    RED_LIGHT_GREEN_LIGHT(competitor);

    // after this game there should be 50 competitors alive
    // test this:
    try
    {
        if (Competitors::getNumber_of_competitors_alive() != 50)
        {
            throw "Something went wrong;\nExiting...\n"; // throw exception
        }
    }
    catch (const char *msg)
    {
        std::cout << msg; // print string
        return 1;         // exit program
    }

    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    // after red_light_green_light 50 competitors are alive
    // there are 4 teams
    // this means that every team has 12 competitors and 2 go directly to the next game
    Competitors **team[4][12]; // 4 teams, every team has 12 competitor
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    int team_found = 0;

    // choose 2 random players that go directly in the next game;

    int lucky_player1 = generate_random<int>(0, 98);
    int lucky_player2;
    if (lucky_player1 % 2 != 0) // if number is odd(competitor real index is even, but that competitor is already eliminated)
    {
        lucky_player1++; // so choose the next competitor
    }

    do // to avoid lucky_player1 == lucky_plater2, generate random numbers until lucky_player1 != lucky_player2
    {
        lucky_player2 = generate_random<int>(0, 98);
        if (lucky_player2 % 2 != 0) // if number is odd(competitor real index is even,but that competitor is already eliminated)
        {
            lucky_player2++; // so choose the next competitor
        }

    } while (lucky_player1 == lucky_player2);

    for (int i = 0; i < 99; i += 2) // all competitors with odd real index
    {
        if (i != lucky_player2 && i != lucky_player1) // skip the lucky competitors
        {
            switch (generate_random<int>(0, 80) % 4) // generate random number
            {
            case 0: // if random_number %4 == 0  place competitor i+1 in team1
                if (t1 < 12)
                {
                    team[0][t1++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 1: // if random_number %4 == 1  place competitor i+1 in team2
                if (t2 < 12)
                {
                    team[1][t2++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 2: // if random_number %4 == 2  place competitor i+1 in team3
                if (t3 < 12)
                {
                    team[2][t3++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 3: // if random_number %4 == 3  place competitor i+1 in team4
                if (t4 < 12)
                {
                    team[3][t4++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            }
            // if we did not find a team for current competitor,
            if (team_found == 0) // just search for an empty slot in other teams
            {
                if (t1 < 12)
                {
                    team[0][t1++] = &competitor[i];
                }
                else if (t2 < 12)
                {
                    team[1][t2++] = &competitor[i];
                }
                else if (t3 < 12)
                {
                    team[2][t3++] = &competitor[i];
                }
                else if (t4 < 12)
                {
                    team[3][t4++] = &competitor[i];
                }
            }
            else // we found already a team for curent competitor, so reset team_found for the next competitor
            {
                team_found = 0;
            }
        }
    }

    std::cout << "\nCompetitors that skip the tug of war game: " << competitor[lucky_player1]->getIndex_of_competitor() << ", " << competitor[lucky_player2]->getIndex_of_competitor() << std::endl;

    TUG_OF_WAR(team);

    // if 2 or more teams had same weight == max weight =>those teams were not eliminated
    // so now there are 14, 26, 38 or 50 competitors left
    // test this:
    try
    {
        // if number of competitors alive -2(those who skip this game) is not a power of 12 or (!) 14 < num_alive < 50
        if ((Competitors::getNumber_of_competitors_alive() - 2) % 12 != 0 || Competitors::getNumber_of_competitors_alive() > 50 || Competitors::getNumber_of_competitors_alive() < 14)
        {
            throw "Something went wrong;\nExiting...\n"; // throw exception
        }
    }
    catch (const char *msg)
    {
        std::cout << msg; // print string
        return 1;         // exit program
    }
    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    // search for pairs of competitors alive for the next game
    int k = 0, p = 98;
    breakk = 0;
    int breakk2 = 0;

    std::cout << "\nMARBLES BEGINS!\n\n";
    // k starts from the begining(from 0) and p starts from the end( from 98)

    // search for pairs until k < p
    while (k < p)
    {
        if (breakk == 0) // if we did not find yet a competitor alive
        {
            if (competitor[k]->get_alive() == true) // if competitor k+1 is alive
            {
                breakk = 1; // set that we find it;
            }
            else // else check next competitor
            {
                k++;
            }
        }
        if (breakk2 == 0) // if we did not find yet a competitor alive
        {
            if (competitor[p]->get_alive() == true) // if competitor p+1 is alive
            {
                breakk2 = 1; // set that we find it
            }
            else // else check next competitor
            {
                p--;
            }
        }

        if (breakk == 1 && breakk2 == 1) // if we found a pair of competitors alive
        {

            try
            {
                MARBLES(competitor[k], generate_random<int>(1, 100), competitor[p], generate_random<int>(1, 100));
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }

            breakk = 0; // reset the breakk and breakk2
            breakk2 = 0;
            k++; // search for the next pair
            p--;
        }
    }

    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    k = 98;
    p = 98; // start from last competitor
    breakk = 0;
    breakk2 = 0;
    int result;

    std::cout << "\nGENKEN BEGINS!\n";

    while (k > 0 && p >= 0) // p should be always smaller then k
    {

        if (breakk == 0) // we have not found first competitor alive from top to bottom;
        {
            if (competitor[k]->get_alive() == true) // if current competitor is alive
            {
                breakk = 1; // set that we found it
                p = k - 1;  // p starts 1 index below k
            }
            else // else current competitor is not alive
            {
                k--; // check next competitor
            }
        }
        else // if we find first competitor alive from top to bottom, start searching for the second;
        {
            if (breakk2 == 0) // if we did not find yet a competitor alive
            {
                if (competitor[p]->get_alive() == true) // if it is alive
                {
                    breakk2 = 1; // set that we found it
                }
                else // else current competitor si eliminated
                {
                    p--; // check next competitor
                }
            }
        }

        if (breakk == 1 && breakk2 == 1) // if we find a pair of competitors alive
        {
            // repeat until one competitor is eliminated
            do
            {
                try
                {
                    result = GENKEN(competitor[k], generate_random<int>(1, 3), competitor[p], generate_random<int>(1, 3));
                }
                catch (const char *msg)
                {
                    std::cout << msg;
                    return 1;
                }
            } while (result == 0);

            if (competitor[k]->get_alive() == false) // competitor k+1 was eliminated
            {
                k = p;       // index k = p;
                p--;         // now p starts 1 position below k
                breakk2 = 0; // k stays on the current alive competitor, and with p we search for the next competitor alive
            }
            else if (competitor[p]->get_alive() == false) // competitor p+1 was eliminated
            {
                breakk2 = 0; // k is alive, so search for the second competitor alive with p
            }
        }
    }
    // after this game only 1 competitor should be alive
    // test this:
    try
    {
        if (Competitors::getNumber_of_competitors_alive() != 1)
        {
            throw "Something went wrong;\nExiting...\n"; // throw exception
        }
    }
    catch (const char *msg)
    {
        std::cout << msg; // print string
        return 1;         // exit program
    }

    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    // find the index of the winner and calculate the sum of debts for competitors eliminated
    int index_of_winner, index_of_supervisor_of_winner;
    int sum_of_debts = 0;
    int total_debt = 0;

    // find team of supervisors that won the most money
    Aux rectangle("rectangle"), circle("circle"), triangle("triangle"); // create an object for every team of supervisors

    for (int i = 0; i < 9; i++) // 9 supervisors
    {
        sum_of_debts = 0;                                                                                                          // the sum starts from 0 for every supervisor                                                                                                   // sum of debts for every supervisor
        for (std::vector<int>::iterator it = supervisor[i]->isSupervising.begin(); it != supervisor[i]->isSupervising.end(); it++) // every supervisor supervises 11 competitors
        {
            if (competitor[*it]->get_alive() == false) // competitor that was supervised by supervisor[i] was eliminated
            {
                sum_of_debts += competitor[*it]->getDebt(); // supervisor[i] receives his debt
                total_debt += competitor[*it]->getDebt();   // in the same iteration calculate the total debt for the winner
            }
            else // it s the winner
            {
                index_of_supervisor_of_winner = i;                           // save his index of supervisor of the winner
                index_of_winner = *it;                                       // save index of winner
                sum_of_debts += competitor[index_of_winner]->getDebt() * 10; // supervisor receives winner's debt * 10;
            }
        }
        // now debt is used to store the amount of money every player has won
        supervisor[i]->setDebt(sum_of_debts - supervisor[i]->getDebt());

        // calculate how much money every team of supervisors won
        if (supervisor[i]->getMask_shape() == "rectangle")
        {
            rectangle.add(sum_of_debts); // for team with rectangle masks
        }
        else if (supervisor[i]->getMask_shape() == "triangle")
        {
            triangle.add(sum_of_debts); // for team with triangle mask
        }
        else if (supervisor[i]->getMask_shape() == "circle")
        {
            circle.add(sum_of_debts); // for team with circle mask
        }
    }

    // now debt is used to store the amount of money every player has won
    competitor[index_of_winner]->setDebt(total_debt - competitor[index_of_winner]->getDebt());

    // print winner
    std::cout << "=======================================================================================\n";
    std::cout << "=======================================================================================\n";
    std::cout << "=======================================================================================\n";
    std::cout << "\nTHE WINNER OF THE GAME:\n[Competitor]: ";
    std::cout << competitor[index_of_winner]->getFirstName() << " " << competitor[index_of_winner]->getLastName() << ", from " << competitor[index_of_winner]->getCity() << std::endl;
    std::cout << "Winner won: " << competitor[index_of_winner]->getDebt() << std::endl;

    // print all supervisors descendig by the money they won
    std::cout << "=======================================================================================\n";

    // sort and print all supervisor
    SORT_SUPERVISORS(supervisor);

    for (int i = 0; i < 9; i++)
    {
        std::cout << "[Supervisor]: " << supervisor[i]->getFirstName() << " " << supervisor[i]->getLastName() << " [" << supervisor[i]->getMask_shape() << " mask], from: " << supervisor[i]->getCity() << ", won: " << supervisor[i]->getDebt() << std::endl;
    }

    std::cout << std::endl;
    
    // print the team/teams of supervisors with the most money
    if (circle.getSum() >= triangle.getSum() && circle.getSum() >= rectangle.getSum())
    {
        circle.print();
    }
    if (triangle.getSum() >= circle.getSum() && triangle.getSum() >= rectangle.getSum())
    {
        triangle.print();
    }
    if (rectangle.getSum() >= circle.getSum() && rectangle.getSum() >= triangle.getSum())
    {
        rectangle.print();
    }

    // free the memory
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