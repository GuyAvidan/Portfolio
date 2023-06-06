#include <iostream>
#include <vector>

#include "joke.hpp"
#include "kaboom.hpp"
#include "surpriser.hpp"
#include "bell.hpp"
#include "surpriserAction.hpp"

static const int NUM_OF_ARGS = 2;

int main()
{
    std::vector<SurpriserAction*> actions;
    actions.push_back(new Joke);
    actions.push_back(new Kaboom{});
    actions.push_back(new Bell);
    Surpriser surpriser(actions);
    surpriser.Run();
    for(const auto& action : actions)
    {
        delete action;
    }
    

}
