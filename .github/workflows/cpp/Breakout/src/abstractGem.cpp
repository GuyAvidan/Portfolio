#include <SFML/Graphics.hpp>

#include "abstractGem.hpp"

AbstractGem::AbstractGem()
{
}

void AbstractGem::SetType(std::vector<sf::Texture*> a_textures)
{
    m_shape.setTexture(TextureType(a_textures));
    m_type = GemTypeType();
}

void AbstractGem::Update(float a_delta)
{  
   	m_shape.move(0, a_delta);
}

void AbstractGem::Draw(sf::RenderWindow& a_window) const
{
    a_window.draw(m_shape);
}

void AbstractGem::SetRadius(float a_radius)
{
    m_shape.setRadius(a_radius);
}

void AbstractGem::SetPosition(sf::Vector2f a_position)
{
    m_shape.setPosition(a_position);
}

void AbstractGem::SetVelocity(sf::Vector2f a_velocity)
{
    return;
}

sf::Vector2f AbstractGem::GetPosition() const
{
    return m_shape.getPosition();
}

float AbstractGem::GetRadius() const
{
    return m_shape.getRadius();
}

float AbstractGem::GetPosX() const 
{ 
    return m_shape.getPosition().x; 
}

float AbstractGem::GetPosY() const 
{ 
    return m_shape.getPosition().y; 
}

sf::Vector2f AbstractGem::Left() const 
{ 
    return sf::Vector2f(GetPosX(), GetPosY() + GetRadius());
}

sf::Vector2f AbstractGem::Right() const 
{ 
    return sf::Vector2f(GetPosX() +  2 * GetRadius(), GetPosY() + GetRadius());
}

sf::Vector2f AbstractGem::Top() const 
{ 
    return sf::Vector2f(GetPosX() + GetRadius(), GetPosY());

}

sf::Vector2f AbstractGem::Bottom() const 
{ 
    return sf::Vector2f(GetPosX() + GetRadius(), GetPosY() + 2 * GetRadius());
}
