#include <iostream>
#include "Header files/functions.h"

// aux method to print all data on columns (the space between columns is the same, although the names have different sizes)
void space(std::string &string, int n)
{
    int initial_length = string.length(); // save the initial length of the string, because we will modify the length every iteration
    for (int i = initial_length; i < n * 15; i++)
    {
        string.append(" ");
    }
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