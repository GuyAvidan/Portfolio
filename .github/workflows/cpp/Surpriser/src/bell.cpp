#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "bell.hpp"

void Bell::Do() const
{
    std::cout << "bell ring\n";
    std::cout << '\a';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << '\a';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << '\a';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}