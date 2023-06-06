#include <SFML/Graphics.hpp>

#include "minusScoreGem.hpp"

const sf::Texture* MinusScoreGem::TextureType(std::vector<sf::Texture*> a_textures) const
{
    return a_textures[13];
}

void MinusScoreGem::PaddleCollide(int &a_live, size_t &a_score) const
{
    a_score -= 100;
}

float MinusScoreGem::GetDeltaVelocity() const
{
    return m_deltaVelocity;
}

GemType MinusScoreGem::GemTypeType() const
{
    return GemType::MINUS_SCORE;
}
