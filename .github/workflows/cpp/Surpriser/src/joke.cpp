#include <string>
#include <iostream>

#include "joke.hpp"
#include "client.hpp"



Joke::Joke(const char * a_argument) 
{
    if(a_argument != nullptr)
    {
        std::string argument = a_argument;
        if(argument == "noenter")
        {
            m_enter = false;
        } 
        else if(argument == "waittcp")
        {
            m_enter = false;
            m_connection = true;            
        } 
        else 
        {
            m_fileName = argument;
        }
    } 
    
}

void Joke::Do() const
{
    std::cout << "When is the best time to put a chicken in the oven?\n";
    if(m_enter)
    {
        std::cout << "Press Enter to find out...";
        std::cin.ignore();
    }
    if (m_connection)
    {
        Client client("127.0.0.1",1990);
        std::cout << "Waiting for connection to port 1990...\n";
        if(!client.Connect())
        {
            std::cout << "no connection\n";
            return;
        }
    }
    std::cout << "After she is dead." << std::endl;
}
