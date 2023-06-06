
#include <SFML/Graphics.hpp>

#include "abstractBrick.hpp"

AbstractBrick::AbstractBrick()
{
    m_shape.setPosition(300,50);
    m_shape.setSize(sf::Vector2f(100, 20));
    m_shape.setOrigin(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);
}

AbstractBrick::AbstractBrick(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setOrigin(size.x / 2.f, size.y / 2.f);
}

void AbstractBrick::SetType(ResManager a_manager)
{
    m_shape.setTexture(ColorType(a_manager));
    m_hits = HitType();
    if(m_hits == 6){
        m_shape.setFillColor(sf::Color::Green);
    } else if(m_hits == 5){
        m_shape.setFillColor(sf::Color::Red);
    }
    m_type = BrickTypeType();
}

bool AbstractBrick::Intersect(sf::Vector2<float> position) const
{
    return m_shape.getGlobalBounds().contains(position);

}
void AbstractBrick::Draw(sf::RenderWindow& window) const
{ 
    window.draw(m_shape); 
}

void AbstractBrick::Update(float a_x)
{ 
    return; 
}

int AbstractBrick::GetHits() const 
{ 
    return m_hits; 
}

sf::RectangleShape AbstractBrick::GetShape() const
{
    return m_shape;
}

void AbstractBrick::SetHits(int hits, ResManager a_manager) 
{
    m_hits = hits; 
    if(m_hits != 0)
        m_shape.setTexture(a_manager.Get(TextureType(m_hits)).get());
    if(ChangeHit(m_hits)) { 
        m_toDelete = true; 
    } 
}

sf::Vector2f AbstractBrick::GetPosition() const
{
    return m_shape.getPosition();
}

void AbstractBrick::SetPosition(sf::Vector2f a_position)
{
    m_shape.setPosition(a_position);
}

sf::Vector2f AbstractBrick::GetSize() const
{
    return m_shape.getSize();
}

float AbstractBrick::GetPosX() const 
{ 
    return m_shape.getPosition().x;
}

float AbstractBrick::GetPosY() const 
{ 
    return m_shape.getPosition().y; 
}

bool AbstractBrick::ToDelete() const 
{ 
    return m_toDelete;
}

sf::Vector2f AbstractBrick::Left() const
{
    return sf::Vector2f(GetPosX(), GetPosY());
}

sf::Vector2f AbstractBrick::Right() const
{
    return sf::Vector2f(GetPosX() + GetSize().x, GetPosY());
}

sf::Vector2f AbstractBrick::Top() const
{
    return sf::Vector2f(GetPosX() + GetSize().x / 2.0f, GetPosY());
}

sf::Vector2f AbstractBrick::Bottom() const
{
    return sf::Vector2f(GetPosX(), GetPosY() + GetSize().y);
}
