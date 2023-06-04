#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

#include "objectGame.hpp"

class Paddle : ObjectGame {
public:
    Paddle(sf::Vector2f a_position, sf::Vector2f a_size);

    void Update(float a_delta) override;
    void SetPosition(sf::Vector2f position) override;
    void SetTexture(sf::Texture* a_textures);

    float GetSizeY() const;
    float GetSizeX() const;
    bool Intersect(sf::Vector2<float> position) const;

    void Draw(sf::RenderWindow& window) const override;
    sf::Vector2f GetPosition() const override;
    float GetPosX() const override;
	float GetPosY() const override;
	sf::Vector2f Left() const override;
	sf::Vector2f Right() const override;
	sf::Vector2f Top() const override;
	sf::Vector2f Bottom() const override;

private:
    sf::RectangleShape m_shape;
};

#endif
