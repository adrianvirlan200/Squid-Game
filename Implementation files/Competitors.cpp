#include "../Header files/Competitors.h"
#include "../Header files/other.h"

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

// print all data on columns
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