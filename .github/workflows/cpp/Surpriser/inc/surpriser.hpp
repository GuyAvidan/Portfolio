#ifndef SURPRISER_HPP
#define SURPRISER_HPP

#include <vector>
#include "joke.hpp"
#include "kaboom.hpp"
#include "surpriserAction.hpp"

class Surpriser
{
public:
    explicit Surpriser(std::vector<SurpriserAction*> const &a_actions);
    ~Surpriser() = default;

    void Run();

private:
    int ChooseRandNumber() const;

private:
    int m_options;
    std::vector<SurpriserAction*> m_actions;
};

#endif