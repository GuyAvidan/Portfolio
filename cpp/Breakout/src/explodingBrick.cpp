
#include <SFML/Graphics.hpp>
#include <iostream>


#include "explodingBrick.hpp"
#include "abstractBrick.hpp"

bool ExplodingBrick::ChangeHit(int hits) const 
{ 
    if(hits == 0) { 
        return true; 
    } 
    return false;
}

int ExplodingBrick::HitType() const 
{
    return 5;
}

const sf::Texture* ExplodingBrick ::ColorType(ResManager a_manager) const 
{
    return a_manager.Get(TextureType::EXPLODING).get();
}

BrickType ExplodingBrick ::BrickTypeType() const
{
    return BrickType::EXPLODING;
}

int ExplodingBrick::Explode(sf::RectangleShape &a_exploding, sf::Vector2f position ,std::vector<AbstractBrick*> a_bricks, ResManager a_manager)
{
    int exploding=1;
    a_exploding.setPosition(sf::Vector2f(position.x- 10, position.y- 10));
    for(auto& brick: a_bricks) 
    {
        if(a_exploding.getGlobalBounds().intersects(brick->GetShape().getGlobalBounds()) && brick->GetPosition() != position)
        {
            if(brick->BrickTypeType() != BrickType::UNBREAKABLE) {
                brick->SetHits(brick->GetHits() - 1, a_manager);
                if(brick->ToDelete()) {
                    ++exploding;
                    std::cout << "exploding2 = " << exploding << '\n';

                }
            }
        }

    }
    return exploding;    
}

