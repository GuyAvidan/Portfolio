#ifndef OBJECTGAME_HPP
#define OBJECTGAME_HPP

#include <SFML/Graphics.hpp>

class ObjectGame {
public:
    virtual ~ObjectGame() = default;
    virtual void Update(float a_delta) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f GetPosition() const = 0;
    virtual void SetPosition(sf::Vector2f position) = 0;
    virtual float GetPosX() const = 0;
	virtual float GetPosY() const = 0;
	virtual sf::Vector2f Left() const = 0;
	virtual sf::Vector2f Right() const = 0;
	virtual sf::Vector2f Top() const = 0;
	virtual sf::Vector2f Bottom() const = 0;
};

#endif //OBJECT_GAME
