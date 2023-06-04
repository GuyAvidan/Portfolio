#ifndef HARD_BRICK_HPP
#define HARD_BRICK_HPP

#include <SFML/Graphics.hpp>
#include "abstractBrick.hpp"
#include "resManager.hpp"

class HardBrick : public AbstractBrick
{
public:
	using AbstractBrick::AbstractBrick;
	bool ChangeHit(int hits) const override;
	int HitType() const override;
	const sf::Texture* ColorType(ResManager a_manager) const override;
	BrickType BrickTypeType() const override;
	int Explode(sf::RectangleShape &a_exploding, sf::Vector2f position, std::vector<AbstractBrick*> m_bricks, ResManager a_manager) override {return 0;}
};

#endif // HARD_BRICK_HPP