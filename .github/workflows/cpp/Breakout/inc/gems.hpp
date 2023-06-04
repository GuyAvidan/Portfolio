#ifndef GEMS_HPP
#define GEMS_HPP

#include <SFML/Graphics.hpp>

enum class GemType { LIFE, SCORE, W_SCORE, MINUS_SCORE };

class Gems {
public:
    explicit Gems(float m_speed, GemType a_type, sf::Vector2f a_startPosition, sf::RenderWindow& a_window);

    void Fall();
    void Draw();
    void SetEraseFlag();

    GemType GetType() const;
    float GetSize() const;
    float GetPosX() const;
    float GetPosY() const;
    bool ShouldErase() const;
    void PaddleCollide(int& a_live, size_t& a_score) const;
    sf::Vector2f Bottom() const;



private:
    sf::CircleShape m_gem;
    sf::RenderWindow& m_window;
    GemType m_type;
    bool m_eraseFlag = false;
    sf::Vector2f m_startPosition;
    float m_speed;
    sf::Texture m_texture;
};

#endif