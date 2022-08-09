#include "Header files/Players.h"
#include "Header files/Supervisors.h"
#include "Header files/Competitors.h"
#include "Header files/functions.h"
#include "Header files/Aux.h"
#include "Implementation files/template function.h"

// main function
int main()
{
    Competitors *competitor[99]; // array of pointers type Competitors, max 99 elements;
    Supervisors *supervisor[9];  // array of pointers type Supervisors, max 9 elements;

    srand(time(NULL)); // generate the seed for rand() (used to generate random numbers)

    try
    {
        ASSIGN_PLAYERS(supervisor, competitor);
    }
    catch(const char *msg)
    {
        std::cout<< msg;
        return 1;
    }
    
    PRINT_ALL_COMPETITORS_ALIVE(competitor);
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

    // print what competitors are assigned for every supervisor
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
    // k starts from the beginning(from 0) and p starts from the end( from 98)

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

    // print all supervisors descending by the money they won
    std::cout << "=======================================================================================\n";

    // sort and print all supervisor
    MERGE_SORT(supervisor,0 , Supervisors::getNumber_of_supervisors() - 1);

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

    return 0;
}