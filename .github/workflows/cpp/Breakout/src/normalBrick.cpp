
#include <SFML/Graphics.hpp>

#include "normalBrick.hpp"

bool NormalBrick::ChangeHit(int hits) const 
{ 
    if(hits == 0) { 
        return true; 
    } 
    return false;
}

int NormalBrick::HitType() const 
{
    return 1;
}

const sf::Texture* NormalBrick::ColorType(ResManager a_manager) const 
{
    return a_manager.Get(TextureType::NORMAl).get();
}

BrickType NormalBrick::BrickTypeType() const
{
    return BrickType::NORMAl;
}
