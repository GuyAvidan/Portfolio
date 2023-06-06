#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

#include "objectGame.hpp"

class Ball : ObjectGame {
public:
    Ball(sf::Vector2f a_position, sf::Vector2f a_velocity, sf::Color a_color, float a_radius);

    void Update(float a_delta) override;
    void SetPosition(sf::Vector2f position) override;

    void SetVelocity(sf::Vector2f velocity);
    void SetRadius(float a_radius);

    sf::Vector2f GetVelocity() const;
    float GetRadius() const;

    sf::Vector2f GetPosition() const override;
    void Draw(sf::RenderWindow& window) const override;
    float GetPosX() const override;
	float GetPosY() const override;
	sf::Vector2f Left() const override;
	sf::Vector2f Right() const override;
	sf::Vector2f Top() const override;
	sf::Vector2f Bottom() const override;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
};

#endif
