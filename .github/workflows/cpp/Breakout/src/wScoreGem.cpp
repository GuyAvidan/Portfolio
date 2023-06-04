#include <SFML/Graphics.hpp>

#include "wScoreGem.hpp"

const sf::Texture* WScoreGem::TextureType(std::vector<sf::Texture*> a_textures) const
{
    return a_textures[12];
}

void WScoreGem::PaddleCollide(int &a_live, size_t &a_score) const
{
    a_score += 200;
}

float WScoreGem::GetDeltaVelocity() const
{
    return m_deltaVelocity;
}

GemType WScoreGem::GemTypeType() const
{
    return GemType::W_SCORE;
}
