#include <SFML/Graphics.hpp>

#include "ball.hpp"

Ball::Ball(sf::Vector2f a_position, sf::Vector2f a_velocity, sf::Color a_color, float a_radius)
: m_velocity(a_velocity)
{
    m_shape.setFillColor(a_color);
    m_shape.setRadius(a_radius);
    m_shape.setPosition(a_position);
}

void Ball::Update(float a_delta)
{  
   	m_shape.move(a_delta, 0);
}

void Ball::Draw(sf::RenderWindow& a_window) const
{
    a_window.draw(m_shape);
}

void Ball::SetRadius(float a_radius)
{
    m_shape.setRadius(a_radius);
}

void Ball::SetPosition(sf::Vector2f a_position)
{
    m_shape.setPosition(a_position);
}

void Ball::SetVelocity(sf::Vector2f a_velocity)
{
    m_velocity = a_velocity;
}

sf::Vector2f Ball::GetPosition() const
{
    return m_shape.getPosition();
}

sf::Vector2f Ball::GetVelocity() const
{
    return m_velocity;
}

float Ball::GetRadius() const
{
    return m_shape.getRadius();
}

float Ball::GetPosX() const 
{ 
    return m_shape.getPosition().x; 
}

float Ball::GetPosY() const 
{ 
    return m_shape.getPosition().y; 
}

sf::Vector2f Ball::Left() const 
{ 
    return sf::Vector2f(GetPosX(), GetPosY() + GetRadius());
}

sf::Vector2f Ball::Right() const 
{ 
    return sf::Vector2f(GetPosX() +  2 * GetRadius(), GetPosY() + GetRadius());
}

sf::Vector2f Ball::Top() const 
{ 
    return sf::Vector2f(GetPosX() + GetRadius(), GetPosY());

}

sf::Vector2f Ball::Bottom() const 
{ 
    return sf::Vector2f(GetPosX() + GetRadius(), GetPosY() + 2 * GetRadius());
}
