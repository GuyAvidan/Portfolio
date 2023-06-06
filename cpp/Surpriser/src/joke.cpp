#include <string>
#include <iostream>

#include "joke.hpp"

void Joke::Go() const
{
    std::cout << "When is the best time to put a chicken in the oven?\n";
    std::cout << "Press Enter to find out...";
    std::cin.ignore();
    std::cout << "After she is dead." << std::endl;
}
