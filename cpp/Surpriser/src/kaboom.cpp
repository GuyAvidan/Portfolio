#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "kaboom.hpp"


void Kaboom::Go() const
{
    std::cout << "3..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "2..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "1..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for(int i = 0; i< 100; ++i)
    {
        std::cout <<"Kaboom!"<< std::endl;
    }
}