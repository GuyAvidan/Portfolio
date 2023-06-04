#include <SFML/Graphics.hpp>

#include "scoreGem.hpp"

const sf::Texture* ScoreGem::TextureType(std::vector<sf::Texture*> a_textures) const
{
    return a_textures[11];
}

void ScoreGem::PaddleCollide(int &a_live, size_t &a_score) const
{
    a_score += 100;
}

float ScoreGem::GetDeltaVelocity() const
{
    return m_deltaVelocity;
}

GemType ScoreGem::GemTypeType() const
{
    return GemType::SCORE;
}