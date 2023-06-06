#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cassert>

#include "surpriser.hpp"
#include "surpriserAction.hpp"


Surpriser::Surpriser(std::vector<SurpriserAction*> const &a_actions)
:   m_options(a_actions.size())
,   m_actions(a_actions)
{
}

void Surpriser::Run()
{
    m_actions[ChooseRandNumber()]->Go();
}

int Surpriser::ChooseRandNumber() const
{
    srand (time(NULL));
    return rand() % m_options;
}
