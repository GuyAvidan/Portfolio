#include <SFML/Graphics.hpp>

#include "../inc/paddle.hpp"

Paddle::Paddle(sf::Vector2f a_position, sf::Vector2f a_size)
{
    m_shape.setSize(a_size);
    m_shape.setPosition(a_position);
}

void Paddle::Update(float a_delta)
{
    m_shape.move(a_delta, 0);
}

void Paddle::Draw(sf::RenderWindow& a_window) const
{
    a_window.draw(m_shape);
}

void Paddle::SetPosition(sf::Vector2f a_position)
{
    m_shape.setPosition(a_position);
}

sf::Vector2f Paddle::GetPosition() const
{
    return m_shape.getPosition();
}

void Paddle::SetTexture(sf::Texture* a_textures)
{
    m_shape.setTexture(a_textures);
}

bool Paddle::Intersect(sf::Vector2<float> position) const
{
    return m_shape.getGlobalBounds().contains(position);
}

float Paddle::GetSizeX() const
{
    return m_shape.getSize().x;
}

float Paddle::GetSizeY() const
{
    return m_shape.getSize().y;
}

float Paddle::GetPosX() const
{
    return m_shape.getPosition().x; 
}

float Paddle::GetPosY() const
{
    return m_shape.getPosition().y;
}

sf::Vector2f Paddle::Left() const
{
    return sf::Vector2f(GetPosX(), GetPosY());
}

sf::Vector2f Paddle::Right() const
{
    return sf::Vector2f(GetPosX() + GetSizeX(), GetPosY());
}

sf::Vector2f Paddle::Top() const
{
    return sf::Vector2f(GetPosX() + GetSizeX() / 2.0f, GetPosY());
}

sf::Vector2f Paddle::Bottom() const
{
    return sf::Vector2f(GetPosX(), GetPosY() + GetSizeY());
}
