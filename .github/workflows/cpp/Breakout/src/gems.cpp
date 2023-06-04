#include <SFML/Graphics.hpp>
#include <iostream>

#include "gems.hpp"

Gems::Gems(float m_speed, GemType a_type, sf::Vector2f a_startPosition, sf::RenderWindow& a_window)
: m_window(a_window)
, m_type(a_type)
, m_startPosition(a_startPosition)
, m_speed(m_speed)
{
    if(m_type == GemType::LIFE){
        if(!m_texture.loadFromFile("../res/liveGem.png")){
            throw std::invalid_argument("Invalild image!");
        }
        std::cout << "gems draw\n";
        m_gem.setFillColor(sf::Color::Blue);
        m_gem.setTexture(&m_texture);
    }
    else if(m_type == GemType::SCORE){
        if(!m_texture.loadFromFile("../res/scoreGem.png")){
            throw std::invalid_argument("Invalild image!");
        }
        m_gem.setTexture(&m_texture);
    }
    else if(m_type == GemType::W_SCORE){
        if(!m_texture.loadFromFile("../res/wScoreGem.png")){
            throw std::invalid_argument("Invalild image!");
        }
        m_gem.setTexture(&m_texture);
        
    } else {
        if(!m_texture.loadFromFile("../res/minusScoreGem.png")){
            throw std::invalid_argument("Invalild image!");
        }
        m_gem.setTexture(&m_texture);
    }
    m_gem.setPosition(m_startPosition);
    m_gem.setRadius(10);
}

void Gems::Fall()
{
    sf::Vector2f pos = m_gem.getPosition();
    pos.y += m_speed;
    m_gem.setPosition(pos);
}

void Gems::Draw()
{
    // std::cout << "gems draw\n";
    m_window.draw(m_gem);
}

void Gems::SetEraseFlag()
{
    m_eraseFlag = true;
}

GemType Gems::GetType() const
{
    return m_type;
}

float Gems::GetSize() const
{
    return m_gem.getRadius() * 2;
}

float Gems::GetPosX() const
{
    return m_gem.getPosition().x;
}

float Gems::GetPosY() const
{
    return m_gem.getPosition().y;
}

bool Gems::ShouldErase() const
{
    return m_eraseFlag;
}

void Gems::PaddleCollide(int& a_live, size_t& a_score) const
{
    if(m_type == GemType::LIFE){
        ++a_live;
    }
    else if(m_type == GemType::SCORE){
        a_score += 100;
    }
    else if(m_type == GemType::W_SCORE){
        a_score += 200;
    } else {
        a_score -= 100;
    }
}

sf::Vector2f Gems::Bottom() const 
{ 
    return sf::Vector2f(GetPosX() + GetSize() / 2, GetPosY() + 2 * GetSize() / 2);
}
