// class for supervisor
#pragma once
#include "Players.h"

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
    Supervisors();                                 // default constructor
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