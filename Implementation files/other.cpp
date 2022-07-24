#include "../Header files/other.h"

// aux method to print all data on columns (the space between columns is the same, although the names have different sizes)
void space(std::string &string, int n)
{
    int initial_length = string.length(); // save the initial length of the string, because we will modify the length every iteration
    for (int i = initial_length; i < n * 15; i++)
    {
        string.append(" ");
    }
}