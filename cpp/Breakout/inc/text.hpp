#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>

class Text
{
public:
    Text();
    Text(const std::string& a_string, const sf::Font& a_font, unsigned int a_characterSize, const sf::Vector2f& a_pos, const sf::Color& a_color);

    void SetString(const std::string& a_string);
    void SetFont(const sf::Font& a_font);
    void SetCharacterSize(unsigned int a_characterSize);
    void SetColor(const sf::Color& a_color);
    void SetPosition(const sf::Vector2f& a_position);

    const std::string& GetString() const;
    const sf::Font& GetFont() const;
    unsigned int GetCharacterSize() const;
    const sf::Color& GetColor() const;
    const sf::Vector2f& GetPosition() const;

    void Draw(sf::RenderWindow& a_window) const;

private:
    sf::Text m_text;
};

#endif // TEXT_HPP
