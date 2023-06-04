#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "abstractBrick.hpp"
#include "resManager.hpp"

class Level {
public:
    std::vector<AbstractBrick*> RunLevel(std::string a_fileName, ResManager a_resManager);
};

#endif
