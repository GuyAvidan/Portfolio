
#include <SFML/Graphics.hpp>

#include "hardBrick.hpp"

bool HardBrick::ChangeHit(int hits) const 
{ 
    if(hits == 0) { 
        return true; 
    } 
    return false;
}

int HardBrick::HitType() const 
{
    return 3;
}

const sf::Texture* HardBrick::ColorType(ResManager a_manager) const 
{
    return a_manager.Get(TextureType::HARD).get();
}

BrickType HardBrick::BrickTypeType() const
{
    return BrickType::HARD;
}
