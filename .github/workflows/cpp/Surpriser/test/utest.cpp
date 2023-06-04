#include <iostream>
#include <vector>

#include "joke.hpp"
#include "kaboom.hpp"
#include "surpriser.hpp"
#include "bell.hpp"
#include "surpriserAction.hpp"

static const int NUM_OF_ARGS = 2;

int main(int argc, char *argv[])
{
    if (argc > NUM_OF_ARGS)
    {
        return 1;
    }
    std::vector<SurpriserAction*> actions;
    actions.push_back(new Joke{argv[1]});
    actions.push_back(new Kaboom{});
    actions.push_back(new Bell);
    Surpriser surpriser(actions);
    surpriser.Run();
    for(const auto& action : actions)
    {
        delete action;
    }
    

}
