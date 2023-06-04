#ifndef BELL_HPP
#define BELL_HPP



#include "surpriserAction.hpp"

class Bell : public SurpriserAction
{
public:
    Bell() = default ;
    ~Bell() = default ;

    void Do() const;
};



#endif