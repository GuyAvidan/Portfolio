#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include "gems.hpp"
#include "paddle.hpp"

class Bonus{
public:
    Bonus();
    Bonus(sf::RenderWindow& a_window);

    void RunBonus(int &a_live, size_t &a_score, Paddle a_paddle);
    void Draw();
    bool IsDone() const;
private:
    std::vector<Gems> m_gems;
};

#endif
