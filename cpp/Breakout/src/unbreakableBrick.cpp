
#include <SFML/Graphics.hpp>

#include "unbreakableBrick.hpp"

bool UnbreakableBrick::ChangeHit(int hits) const 
{ 
    return false;
}

int UnbreakableBrick::HitType() const 
{
    return 10000;
}

const sf::Texture* UnbreakableBrick::ColorType(ResManager a_manager) const 
{
    return a_manager.Get(TextureType::UNBREAKABLE).get();
}

BrickType UnbreakableBrick::BrickTypeType() const
{
    return BrickType::UNBREAKABLE;
}
