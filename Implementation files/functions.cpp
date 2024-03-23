#include <iostream>
#include "../Header files/functions.h"
#include "template function.h"

void ASSIGN_PLAYERS(Supervisors *supervisor[], Competitors *competitor[])
{
    int current_number_of_supervisors = 0;
    int current_number_of_competitors = 0;

    for (int i = 0; i < 108; i++) // dynamically allocate memory for each player;
    {
        // generate the names randomly;
        // we declare 3 string variables to store the name themselves and
        // 3 additional int variables to generate random lengths of the names
        std::string first_name, last_name, city;
        int max_Fname_length, max_Lname_length, max_city_length;

        // pick random lengths of the names(between 3 and 10 characters)
        max_Fname_length = generate_random<int>(3, 10);
        max_Lname_length = generate_random<int>(3, 10);
        max_city_length = generate_random<int>(3, 10);

        // generate the first letter of the name randomly
        first_name.push_back(generate_random<char>(65, 90)); // first letter is in upper case
        last_name.push_back(generate_random<char>(65, 90));  // first letter is in upper case
        city.push_back(generate_random<char>(65, 90));       // first letter is in upper case

        // generate the remaining letters of the name(only letters lower case)
        for (int i = 1; i < max_Fname_length; i++)
        {
            first_name.push_back(generate_random<char>(97, 122));
        }
        for (int i = 1; i < max_Lname_length; i++)
        {
            last_name.push_back(generate_random<char>(97, 122));
        }
        for (int i = 1; i < max_city_length; i++)
        {
            city.push_back(generate_random<char>(97, 122));
        }

        /* Now we need to assign a player as a competitor or as a supervisor. The algorithm used is described below.
        Firstly, we generate a random number, between 0 and 25. If this number can be divided by 5 => the current 
        player is a supervisor, otherwise it is a competitor.
        Repeat the process for each player until all slots for a class of supervisors are taken.
        If one class of supervisors is full, then search for another free slot in others classes.
        If no other slot is available for supervision, then the current player will be considered a competitor.
        In the same way, if no slots for competitors is available, then the current player is a supervisor.
         */

        bool assigned = false; // true if the current player was assigned, false otherwise
        // generate a random number;
        int dummy_number;
        dummy_number = generate_random<int>(0, 25);

        if (dummy_number % 5 == 0) // if true => the current player it's a supervisor
        {
            if (current_number_of_supervisors < 9) // there are free supervisor slots
            {
                switch (generate_random<int>(1, 3) % 3) // random number between 1 and 3 to chose the type of mask
                {
                case 0:                                                             // circle mask
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // there are les than 3 circle mask supervisors
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    break;
                case 1:                                                                // rectangle mask
                    if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3) // there are less than 3 rectangle mask supervisors
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    break;
                case 2: // triangle
                    if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3)
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                    break;
                }
                if (assigned == false) // if current player could not be assigned, search for and empty place in the team of supervisors
                {
                    if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3) // add circle mask if available
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "circle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_rectangle_mask() < 3) // add rectangle mask if available
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "rectangle");
                    }
                    else if (Supervisors::get_num_of_supervisors_with_triangle_mask() < 3) // add triangle mask if available
                    {
                        assigned = true; // the current player was assigned
                        supervisor[current_number_of_supervisors++] = new Supervisors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100), "triangle");
                    }
                }
                else // (assigned == true) a player has been assigned as a supervisor successfully
                {   
                    //reset the flag for the next player
                    assigned = 0;
                }
            }
            else // else all slots for supervisors are occupied, add current user as a competitor
            {
                if (current_number_of_competitors < 99)
                {
                    competitor[current_number_of_competitors++] = new Competitors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100));
                }
            }
        }
        else // it's a competitor
        {
            if (current_number_of_competitors < 99) // if there are free slots for competitors, add current user as a competitor
            {
                competitor[current_number_of_competitors++] = new Competitors(first_name, last_name, city, generate_random<int>(10000, 100000), generate_random<int>(50, 100));
            }
            // if there are not free slots available for competitors, add current player as a supervisor(repeat the process of adding a supervisor)
            else if (Supervisors::get_num_of_supervisors_with_circle_mask() < 3)
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
}

/* This function is an auxiliary function used to display the supervisors and the competitors
on columns in an arranged way. Basically, it help us to generate a variable number of blank spaces
dependant of the lengths of the words. In this way, every column will be indented nicely.
*/
void space(std::string &string, int n)
{
    int initial_length = string.length(); // save the initial length of the string, because we will modify the length every iteration
    for (int i = initial_length; i < n * 15; i++)
    {
        string.append(" ");
    }
}

// function used to print all supervisors
void PRINT_ALL_SUPERVISORS(Supervisors *supervisor[])
{
    std::cout << "\nAll supervisors:\n";
    std::cout << "First Name     Last Name      Mask Shape     City           Debt           Weight" << std::endl;
    std::cout << "---------------------------------------------------------------------------------\n";

    for (int supervisor_cnt = 0; supervisor_cnt < Supervisors::getNumber_of_supervisors(); supervisor_cnt++)
    {
        supervisor[supervisor_cnt]->print_all_data();
    }
}

// auxiliary function used in the implementation of the merge sort algorithm
void MERGE(Supervisors *supervisor[], int const left, int const mid, int const right)
{
    // calculate the dimensions of the sub arrays
    int left_subArray_length = mid - left + 1; //[left ... mid]
    int right_subArray_length = right - mid;   //[mid + 1 ... end]

    // create the temporary arrays
    Supervisors **leftArray = new Supervisors *[left_subArray_length];
    Supervisors **rightArray = new Supervisors *[right_subArray_length];

    // copy the data from the initial array to the temporary arrays
    for (int i = 0; i < left_subArray_length; i++)
    {
        leftArray[i] = supervisor[i + left];
    }
    for (int i = 0; i < right_subArray_length; i++)
    {
        rightArray[i] = supervisor[i + mid + 1];
    }

    int rightArray_index = 0;
    int leftArray_index = 0;
    int mergedArray_index = left;

    // reassemble the array descending by the amount of money won(that is store as debt)
    while (leftArray_index < left_subArray_length && rightArray_index < right_subArray_length)
    {
        if (leftArray[leftArray_index]->getDebt() >= rightArray[rightArray_index]->getDebt())
        {
            supervisor[mergedArray_index++] = leftArray[leftArray_index++];
        }
        else
        {
            supervisor[mergedArray_index++] = rightArray[rightArray_index++];
        }
    }

    // add the remaining elements if there are any
    while (leftArray_index < left_subArray_length)
    {
        supervisor[mergedArray_index++] = leftArray[leftArray_index++];
    }
    while (rightArray_index < right_subArray_length)
    {
        supervisor[mergedArray_index++] = rightArray[rightArray_index++];
    }

    // free the memory
    delete[] leftArray;
    delete[] rightArray;
}

void MERGE_SORT(Supervisors *supervisor[], int const left, int const right)
{
    if (left >= right)
    {
        return;
    }

    // calculate the middle index of the array
    int mid = left + (right - left) / 2;

    // break the array recursively in half
    MERGE_SORT(supervisor, left, mid);
    MERGE_SORT(supervisor, mid + 1, right);
    // merge the sub arrays together
    MERGE(supervisor, left, mid, right);
}

// function used to print all competitors that are not yet eliminated
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
    // calculate the total weight for each team
    for (int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            sum[j] += (*team[j][i])->getWeight();
        }
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