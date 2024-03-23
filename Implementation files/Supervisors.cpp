#include "../Header files/Supervisors.h"
#include "../Header files/functions.h"

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