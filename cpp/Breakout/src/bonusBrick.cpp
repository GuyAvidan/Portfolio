
#include <SFML/Graphics.hpp>

#include "bonusBrick.hpp"

bool BonusBrick::ChangeHit(int hits) const 
{ 
    if(hits == 0) { 
        return true; 
    } 
    return false;
}

int BonusBrick::HitType() const 
{
    return 6;
}

const sf::Texture* BonusBrick::ColorType(ResManager a_manager) const 
{
    return a_manager.Get(TextureType::BONUS).get();
}

BrickType BonusBrick::BrickTypeType() const
{
    return BrickType::BONUS;
}