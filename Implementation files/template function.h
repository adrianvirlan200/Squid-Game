//implementation of generate_random template function
template <class T>
T generate_random(int min, int max)
{
    // generate random number between min and max values
    return (std::rand()) % (max - min + 1) + min;
}

#include "../Header files/other.h"