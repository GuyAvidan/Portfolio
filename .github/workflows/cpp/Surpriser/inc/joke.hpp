#ifndef JOKE_HPP
#define JOKE_HPP

#include <iostream>

#include "surpriserAction.hpp"


class Joke : public SurpriserAction
{
public:
    Joke(const char * a_argument);
    ~Joke() = default;

    void Do() const;

private:
    bool m_enter = true;
    bool m_connection = false;
    std::string m_fileName;
};



#endif