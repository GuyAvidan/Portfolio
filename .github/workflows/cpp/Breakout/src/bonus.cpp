#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "bonus.hpp"
#include "gems.hpp"
#include "paddle.hpp"

Bonus::Bonus()
: m_gems() 
{
}

Bonus::Bonus(sf::RenderWindow& a_window)
: m_gems() 
{
    //for (int i = 0; i < 5; ++i)
    //{
        Gems tempGem = Gems(1, GemType::LIFE, sf::Vector2f(a_window.getSize().x / 2, a_window.getSize().y - 200), a_window);
        m_gems.emplace_back(tempGem);
    //}
}

void Bonus::RunBonus(int &a_live, size_t &a_score, Paddle a_paddle)
{
    for (auto& gem : m_gems) {
        if(a_paddle.Intersect(gem.Bottom())) {
            gem.PaddleCollide(a_live, a_score);
            gem.SetEraseFlag();
        }
        gem.Fall();
    }
}

void Bonus::Draw()
{
    for (auto& gem : m_gems) {
        gem.Draw();
    }
}

bool Bonus::IsDone() const
{
    for (auto& gem : m_gems) {
        if(!gem.ShouldErase())
        {
            return false;
        }
    }
    return true;
}



