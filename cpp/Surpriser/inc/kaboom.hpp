#ifndef KABOOM_HPP
#define KABOOM_HPP



#include "surpriserAction.hpp"

class Kaboom : public SurpriserAction
{
public:
    Kaboom() = default ;
    ~Kaboom() = default ;

    void Go() const override;
};



#endif