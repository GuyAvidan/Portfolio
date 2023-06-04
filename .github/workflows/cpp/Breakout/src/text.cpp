#include <SFML/Graphics.hpp>

#include <iostream>

#include "text.hpp"

Text::Text()
: m_text()
{
}

Text::Text(const std::string& a_string, const sf::Font& a_font, unsigned int a_characterSize, const sf::Vector2f& a_pos, const sf::Color& a_color)
: m_text()
{
    m_text.setString(a_string);
    m_text.setFont(a_font);
    m_text.setCharacterSize(a_characterSize);
    m_text.setPosition(a_pos);
    m_text.setColor(a_color);
}

void Text::SetString(const std::string& a_string)
{
    m_text.setString(a_string);
}

void Text::SetFont(const sf::Font& a_font)
{
    m_text.setFont(a_font);
}

void Text::SetCharacterSize(unsigned int a_characterSize)
{
    m_text.setCharacterSize(a_characterSize);
}

void Text::SetColor(const sf::Color& a_color)
{
    m_text.setColor(a_color);
}

void Text::SetPosition(const sf::Vector2f& a_position)
{
    m_text.setPosition(a_position);
}

const std::string& Text::GetString() const
{
    return m_text.getString();
}

unsigned int Text::GetCharacterSize() const
{
    return m_text.getCharacterSize();
}

const sf::Color& Text::GetColor() const
{
    return m_text.getFillColor();
}

const sf::Vector2f& Text::GetPosition() const
{
    return m_text.getPosition();
}

void Text::Draw(sf::RenderWindow& a_window) const
{
    a_window.draw(m_text);
}
