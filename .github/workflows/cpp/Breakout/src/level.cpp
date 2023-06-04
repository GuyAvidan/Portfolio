#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "level.hpp"
#include "abstractBrick.hpp"
#include "normalBrick.hpp"
#include "hardBrick.hpp"
#include "unbreakableBrick.hpp"
#include "bonusBrick.hpp"
#include "explodingBrick.hpp"
#include "resManager.hpp"

static AbstractBrick* newBrick( int a_type);

std::vector<AbstractBrick*> Level::RunLevel(std::string a_fileName, ResManager a_resManager)
{
    std::vector<AbstractBrick*> bricks;
    std::ifstream myFile (a_fileName);
    if (!myFile)
    {
        std::cerr<<"Could not open file\n";
    }
    int type = 0;
    float x = 0;
    float y = 0;
    while(myFile.good())
    {
        myFile >> type >> x >> y ;
        AbstractBrick* tempBrick = newBrick(type);
        tempBrick->SetPosition(sf::Vector2f(x, y));
        tempBrick->SetType(a_resManager);
        bricks.emplace_back(tempBrick);
    }
    return bricks;
}

static AbstractBrick* newBrick( int a_type)
{
    if (a_type == 1){
        return new NormalBrick;
    } else if (a_type == 2) {
        return new HardBrick;
    } else if (a_type == 3) {
        return new UnbreakableBrick;
    } else if (a_type == 4) {
        return new BonusBrick;
    } else if (a_type == 5) {
        return new ExplodingBrick;
    }
}
