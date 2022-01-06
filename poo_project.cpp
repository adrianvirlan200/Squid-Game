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

    std::string getFirstName();
    std::string getLastName();
    std::string getCity();
    int getDebt();
    int getWeight();
    void setDebt(int);
};
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
class Competitors : public Players
{
public:                                     // private
    int index = 0;                          // index of competitor
    static int number_of_competitors_alive; // static variable that stores the number of competitors(number of objects created)
    std::string isSupervisedBy;             // stores the supervisor allocated for current

    // public:
    Competitors(std::string first_name, std::string last_name, std::string city, int debt, int weight) : Players(first_name, last_name, city, debt, weight) // constructor
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
    bool get_alive();
    friend void PRINT_ALL_COMPETITORS(Competitors);
    friend void PRINT_ALL_COMPETITORS_ALIVE(Competitors);
};

int Competitors::number_of_competitors_alive = 0;

bool Competitors::get_alive()
{
    if (this->is_alive == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
        std::cout << this->first_name << std::setw(15) << this->last_name << std::setw(15) << this->index << std::setw(15) << this->city << std::setw(15) << this->debt << std::setw(15) << this->weight << std::endl;
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
    friend void PRINT_ALL_SUPERVISORS(Supervisors);
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

// FUNCTIONS

void PRINT_ALL_SUPERVISORS(Supervisors *supervisor[])
{
    std::cout << "\nAll supervisors:\n";
    std::cout << "First Name" << std::setw(15) << "Last Name" << std::setw(15) << "Mask shape" << std::setw(15) << "City" << std::setw(15) << "Debt" << std::setw(15) << "Weight" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        supervisor[i]->print_all_data();
    }
}

void PRINT_ALL_COMPETITORS(Competitors *competitor[])
{
    std::cout << "\nAll competitors:\n";
    std::cout << "First Name" << std::setw(15) << "Last Name" << std::setw(15) << "Index" << std::setw(15) << "City" << std::setw(15) << "Debt" << std::setw(15) << "Weight" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
    for (int i = 0; i < 99; i++)
    {
        competitor[i]->print_all_data();
    }
}
void PRINT_ALL_COMPETITORS_ALIVE(Competitors *competitor[])
{
    std::cout << "\nAll competitors Alive:\n";
    std::cout << "First Name" << std::setw(15) << "Last Name" << std::setw(15) << "Index" << std::setw(15) << "City" << std::setw(15) << "Debt" << std::setw(15) << "Weight" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
    for (int i = 0; i < 99; i++)
    {
        competitor[i]->print_competitor_data_if_alive();
    }
}

void RED_LIGHT_GREEN_LIGHT(Competitors *competitor[])
{
    std::cout << "\nRED LIGHT GREEN LIGHT BEGINS!\n";
    for (int i = 1; i < 99; i += 2)
    {
        --(*competitor[i]); // eliminate the competitor
    }
}
void ELIMINATE_TEAM(Competitors **team[])
{
    if ((*team[0])->is_alive == false) // check if 1 player of the team is eliminated->if yes this means that that team is already eliminated
    {
        throw "Team already eliminated or other error;\n"; // throw an error;
    }

    for (int i = 0; i < 12; i++)
    {
        --(**team[i]); // eliminate all competitors of that team
    }
}
void TUG_OF_WAR(Competitors **team1[], Competitors **team2[], Competitors **team3[], Competitors **team4[])
{

    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    // calculate the total weight for every team
    for (int i = 0; i < 12; i++)
    {
        sum1 += (*team1[i])->getWeight();
        sum2 += (*team2[i])->getWeight();
        sum3 += (*team3[i])->getWeight();
        sum4 += (*team4[i])->getWeight();
    }

    std::cout << "\nTUG OF WAR BEGINS!\n";
    std::cout << "\nTeam1:[total weight: " << sum1 << "]\n";
    for (int i = 0; i < 12; i++)
    {
        (*team1[i])->print_all_data();
    }
    std::cout << "Team2:[total weight: " << sum2 << "]\n";
    for (int i = 0; i < 12; i++)
    {
        (*team2[i])->print_all_data();
    }
    std::cout << "Team3:[total weight: " << sum3 << "]\n";
    for (int i = 0; i < 12; i++)
    {
        (*team3[i])->print_all_data();
    }
    std::cout << "Team4:[total weight: " << sum4 << "]\n";
    for (int i = 0; i < 12; i++)
    {
        (*team4[i])->print_all_data();
    }

    // find team max weight
    int sum_max = sum1;
    if (sum_max < sum2)
    {
        sum_max = sum2;
    }
    if (sum_max < sum3)
    {
        sum_max = sum3;
    }
    if (sum_max < sum4)
    {
        sum_max = sum4;
    }
    // eliminate all the teams that have weight lower than max weight
    if (sum_max > sum1) // team1 has lower weight that team with max weight
    {
        try
        {
            ELIMINATE_TEAM(team1); // so eliminate team1
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
    if (sum_max > sum2) // team2 has lower weight that team with max weight
    {
        try
        {
            ELIMINATE_TEAM(team2); // so eliminate team2
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
    if (sum_max > sum3) // team3 has lower weight that team with max weight
    {
        try
        {
            ELIMINATE_TEAM(team3); // so eliminate team3
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
    if (sum_max > sum4) // team4 has lower weight that team with max weight
    {
        try
        {
            ELIMINATE_TEAM(team4); // so eliminate team4
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
}

void MARBLES(Competitors *competitor1, int rand_num_1, Competitors *competitor2, int rand_num_2)
{
    if (competitor1->get_alive() == false || competitor2->get_alive() == false)
    {
        throw "Competitor already eliminated;";
    }

    std::cout << "Competitor with index " << competitor1->getIndex_of_competitor() << " got: " << rand_num_1 << std ::endl;
    std::cout << "Competitor with index " << competitor2->getIndex_of_competitor() << " got: " << rand_num_2 << std ::endl;
    std::cout << "-------\n";

    // competitor with bigger number is eliminated
    if (rand_num_1 > rand_num_2)
    {
        --(*competitor1);
    }
    else if (rand_num_2 > rand_num_1)
    {
        --(*competitor2);
    }
}

std::string GENKEN_AUX(int num)
{
    if (num <= 0 || num > 3)
    {
        throw "Wrong num;\n";
    }
    if (num == 1)
    {
        return "rock";
    }
    else if (num == 2)
    {
        return "paper";
    }
    else if (num == 3)
    {
        return "scissors";
    }
}
//  returns 0 if no competitor was eliminated
int GENKEN(Competitors *competitor1, int num_1, Competitors *competitor2, int num_2)
{

    std::cout << "Competitor with index: " << competitor1->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_1) << std::endl;
    std::cout << "Competitor with index: " << competitor2->getIndex_of_competitor() << " got: " << GENKEN_AUX(num_2) << std::endl;
    std::cout << "-----------\n";

    // rock = 1;
    // paper = 2;
    // scissor = 3;

    switch (num_1 - num_2)
    {
    // both chose the same number
    case 0:
        return 0; // none is eliminated
        break;

    // 1 = paper(2) && 2 = rock(3) => 2 eliminated
    // or 1 = scissors(3) && 2 = paper(2) => 2 eliminated
    case 1:
        --(*competitor2); // in both cases competitor 2 is eliminated;
        break;
    // 1 = scissors(3) && 2 = rock(1) => 1 eliminated
    case 2:
        --(*competitor1); // competitor 1 is eliminated
        break;
    // 1 = rock(1) && 2 = paper(2) => 1 eliminated
    // 1 = paper(2) && 2 = scissors(3) => 1 eliminated;
    case -1:
        --(*competitor1); // in both cases competitor1 is eliminated;
        break;
    // 1 = rock(1) && 2 = scissors(3) => 2 eliminated
    case -2:
        --(*competitor2);
        break;
    }
    return 1; // we eliminate 1 competitor
}
// main function
int main()
{
    Competitors *competitor[99]; // array of pointers type Competitors, max 99 elements;
    Supervisors *supervisor[9];  // array of pointers type Supervisors, max 9 elements;

    int current_number_of_supervisors = 0; // max 8
    int current_number_of_competitors = 0; // max 98

    srand(time(NULL)); // generate the seed for rand() (used to generete random numbers)

    int c;
    for (int i = 0; i < 108; i++) // dynamically allocating memory for every player;
    {
        // if the number between 0-25 generated random is divided by 5 =>that player is a supervisor,else it is a competitor
        // repeat the process for every player until all slots are taken
        // if one class of supervisors is full, then just search for another free slot in others classes
        // if no slot is available, then that player is a competitor

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
                if (c == 0) // if one of 3 slots is full we search for a free slot in other classes of supervisors
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
                else // we added a supervisor, reset c for the next supervisor
                {
                    c = 0;
                }
            }
            else // else all slots for supervisors are occupied, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
        }
        else // it's a competitor
        {
            if (current_number_of_competitors < 99) // if there are free slots for competitors, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors("FirstName", "LastName", "City", generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
            else if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // if there are not free slots available, add current player as a supervisor(repeat the process of adding a supervisor)
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

    PRINT_ALL_COMPETITORS(competitor);
    PRINT_ALL_SUPERVISORS(supervisor);

    int count = 0;
    for (int i = 0; i < 9; i++) // 9 supervisors
    {
        for (int j = 0; j < 11; j++) // each supervisor has 11 competitors to supervise
        {
            supervisor[i]->isSupervising[supervisor[i]->num++] = count++;
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << "Supervisor " << i + 1 << " with " << supervisor[i]->getMask_shape() << " mask is supervising competitor no.:" << std::setw(10);
        for (int j = 0; j < 11; j++)
        {
            std::cout << supervisor[i]->isSupervising[j] + 1 << " ";
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

    std::cout << std::endl;
    for (int i = 0; i < 99; i++)
    {
        std::cout << "Competitor no. " << i + 1 << " is supervised by a supervisor with " << competitor[i]->isSupervisedBy << " mask" << std::endl;
    }

    RED_LIGHT_GREEN_LIGHT(competitor);

    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    // after red_light_green_light 50 competitors are alive
    // this means that every team has 12 competitors and 2 go directly to the next game
    Competitors **team1[12], **team2[12], **team3[12], **team4[12];
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    int team_found = 0;

    // choose 2 random players that go directly in the next game;

    int lucky_player1 = generate_random<int>(0, 98);
    int lucky_player2;
    if (lucky_player1 % 2 != 0) // if number is odd(competitor index is even, but that competitor is already eliminated)
    {
        lucky_player1++; // so choose the next competitor
    }

    do // to avoid lucky_player1 == lucky_plater2, generate random numbers until lucky_player1 != lucky_player2
    {
        lucky_player2 = generate_random<int>(0, 98);
        if (lucky_player2 % 2 != 0) // if number is odd(competitor index is even,but that competitor is already eliminated)
        {
            lucky_player2++; // so choose the next competitor
        }

    } while (lucky_player1 == lucky_player2);

    for (int i = 0; i < 99; i += 2) // all competitors with odd index
    {
        if (i != lucky_player2 && i != lucky_player1) // skip the lucky competitors
        {
            switch (generate_random<int>(0, 80) % 4) // generate random number
            {
            case 0: // if random_number %4 == 0  place competitor i+1 in team1
                if (t1 < 12)
                {
                    team1[t1++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 1: // if random_number %4 == 1  place competitor i+1 in team2
                if (t2 < 12)
                {
                    team2[t2++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 2: // if random_number %4 == 2  place competitor i+1 in team3
                if (t3 < 12)
                {
                    team3[t3++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            case 3: // if random_number %4 == 3  place competitor i+1 in team4
                if (t4 < 12)
                {
                    team4[t4++] = &competitor[i];
                    team_found = 1; // team found for current competitor
                }
                break;
            }
            // if we did not find a team for current competitor,
            if (team_found == 0) // just search for an empty slot in other teams
            {
                if (t1 < 12)
                {
                    team1[t1++] = &competitor[i];
                }
                else if (t2 < 12)
                {
                    team2[t2++] = &competitor[i];
                }
                else if (t3 < 12)
                {
                    team3[t3++] = &competitor[i];
                }
                else if (t4 < 12)
                {
                    team4[t4++] = &competitor[i];
                }
            }
            else // we found already a team for curent competitor, so reset team_found for the next competitor
            {
                team_found = 0;
            }
        }
    }

    std::cout << "\nCompetitors that skip the tug of war game: " << competitor[lucky_player1]->getIndex_of_competitor() << ", " << competitor[lucky_player2]->getIndex_of_competitor() << std::endl;

    TUG_OF_WAR(team1, team2, team3, team4);

    // if 2 or more teams had same weight == max weight =>those teams were not eliminated
    // so now there are 14, 26, 38 or 50 competitors left(so an even number)
    PRINT_ALL_COMPETITORS_ALIVE(competitor);

    // search for pairs of competitors alive for the next game
    int k = 0, p = 98;
    breakk = 0;
    int breakk2 = 0;

    std::cout << "\nMARBLES BEGINS!\n\n";
    // k starts from the begining(from 0) and p starts from the end( from 98)
    // we search for pairs until k < p
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
                p = k - 1;
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
                result = GENKEN(competitor[k], generate_random<int>(1, 3), competitor[p], generate_random<int>(1, 3));

            } while (result == 0);

            if (competitor[k]->get_alive() == false) // competitor k+1 was eliminated
            {
                k = p;
                p--;
                breakk2 = 0; // k stays on the current alive competitor, and with p we search for the next competitor alive
            }
            else if (competitor[p]->get_alive() == false) // competitor p+1 was eliminated
            {
                breakk2 = 0;
            }
        }
    }

    // find the index of the winner and calculate the sum of debts for competitors eliminated
    int index_of_winner, index_of_supervisor_of_winner;
    int sum_of_debts = 0;
    int total_debt = 0;

    for (int i = 0; i < 9; i++) // 9 supervisors
    {
        sum_of_debts = 0;
        for (int j = 0; j < 11; j++) // every supervisor supervises 11 competitors
        {
            if (competitor[supervisor[i]->isSupervising[j]]->get_alive() == false)
            {
                sum_of_debts += competitor[supervisor[i]->isSupervising[j]]->getDebt();
                total_debt += competitor[supervisor[i]->isSupervising[j]]->getDebt();
            }
            else // it s the winner
            {
                index_of_supervisor_of_winner = i;
                index_of_winner = supervisor[i]->isSupervising[j]; // save index
                sum_of_debts += competitor[index_of_winner]->getDebt() * 10;
            }
        }

        supervisor[i]->setDebt(sum_of_debts - supervisor[i]->getDebt());
    }

    competitor[index_of_winner]->setDebt(total_debt - competitor[index_of_winner]->getDebt());

    std::cout << "\nTHE WINNER OF GAME:\n";
    competitor[index_of_winner]->print_competitor_data_if_alive();

    std::cout << "\nAll supervisors:\n";
    std::cout << "First Name" << std::setw(15) << "Last Name" << std::setw(15) << "Mask shape" << std::setw(15) << "City" << std::setw(15) << "Debt" << std::setw(15) << "Weight" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;

    // supervisor of winner will win the biggest amount of money
    
    int previous_max = supervisor[index_of_supervisor_of_winner]->getDebt();
    int sum_max, save_index;
    k = 0;
    while (k < 9)
    {
        sum_max = supervisor[k]->getDebt();
        save_index = k;
        for (int i = 0; i < 9; i++)
        {
            if (supervisor[i]->getDebt() >)
        }
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