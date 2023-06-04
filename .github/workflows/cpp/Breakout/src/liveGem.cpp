#include <SFML/Graphics.hpp>

#include "liveGem.hpp"

const sf::Texture* LiveGem::TextureType(std::vector<sf::Texture*> a_textures) const
{
    return a_textures[10];
}

void LiveGem::PaddleCollide(int &a_live, size_t &a_score) const
{
    ++a_live;
}

float LiveGem::GetDeltaVelocity() const
{
    return m_deltaVelocity;
}

GemType LiveGem::GemTypeType() const
{
    return GemType::LIVE;
}
