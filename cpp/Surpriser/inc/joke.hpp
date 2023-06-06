#ifndef JOKE_HPP
#define JOKE_HPP

#include "surpriserAction.hpp"


class Joke : public SurpriserAction
{
public:
    Joke() = default;
    ~Joke() = default;

    void Go() const;
};



#endif