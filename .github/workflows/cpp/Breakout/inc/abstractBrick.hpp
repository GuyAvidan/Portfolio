#ifndef ABSTRACT_BRICK_HPP
#define ABSTRACT_BRICK_HPP

#include <SFML/Graphics.hpp>

#include "objectGame.hpp"
#include "resManager.hpp"

enum class BrickType { NORMAl, HARD, UNBREAKABLE, BONUS, EXPLODING };

class AbstractBrick : public ObjectGame
{
public:
	
    AbstractBrick();
    AbstractBrick(sf::Vector2f position, sf::Vector2f size);

	void Draw(sf::RenderWindow& window) const;

    void Update(float a_x) override;
    void SetPosition(sf::Vector2f position) override;
    void SetType(ResManager a_manager);

    sf::Vector2f GetSize() const;
	int GetHits() const;
    bool ToDelete() const;
    bool Intersect(sf::Vector2<float> position) const;

    sf::Vector2f GetPosition() const override;
	float GetPosX() const override;
	float GetPosY() const override;
	sf::Vector2f Left() const override;
	sf::Vector2f Right() const override;
	sf::Vector2f Top() const override;
	sf::Vector2f Bottom() const override;
	
    sf::RectangleShape GetShape() const;
    void SetHits(int hits, ResManager a_manager);
    virtual int HitType() const = 0;
	virtual const sf::Texture* ColorType(ResManager a_manager) const = 0;
    virtual BrickType BrickTypeType() const = 0;
    virtual bool ChangeHit(int hits) const = 0;
    virtual int Explode(sf::RectangleShape &a_exploding,sf::Vector2f position, std::vector<AbstractBrick*> m_bricks, ResManager a_manager) = 0;

private:
	sf::RectangleShape m_shape;
	int m_hits = 1;
    bool m_toDelete = false;
    BrickType m_type = BrickType::NORMAl;
};

#endif // NORMAL_BRICK_HPP
