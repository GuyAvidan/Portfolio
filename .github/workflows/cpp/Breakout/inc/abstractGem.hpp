#ifndef ABSTRACT_GEM_HPP
#define ABSTRACT_GEM_HPP

#include <SFML/Graphics.hpp>

#include "objectGame.hpp"

enum class GemType { LIVE, SCORE, W_SCORE, MINUS_SCORE };

class AbstractGem : ObjectGame {
public:
    AbstractGem (); // speed

    void Update(float a_delta) override;
    void SetPosition(sf::Vector2f position) override;

    void SetVelocity(sf::Vector2f velocity);
    void SetRadius(float a_radius);
    void SetType(std::vector<sf::Texture*> a_textures);

    float GetRadius() const;
    sf::Vector2f GetPosition() const override;
    void Draw(sf::RenderWindow& window) const override;
    float GetPosX() const override;
	float GetPosY() const override;
	sf::Vector2f Left() const override;
	sf::Vector2f Right() const override;
	sf::Vector2f Top() const override;
	sf::Vector2f Bottom() const override;

    virtual const sf::Texture* TextureType(std::vector<sf::Texture*> a_textures) const = 0;
    virtual void PaddleCollide(int &a_live, size_t &a_score) const = 0;
    virtual float GetDeltaVelocity() const = 0;
    virtual GemType GemTypeType() const = 0;

private:
    sf::CircleShape m_shape; // position, speed
    GemType m_type = GemType::LIVE;
};

#endif
