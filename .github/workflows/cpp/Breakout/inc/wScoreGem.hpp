#ifndef W_SCORE_GEM_HPP
#define W_SCORE_GEM_HPP

#include <SFML/Graphics.hpp>

#include "abstractGem.hpp"

class WScoreGem : AbstractGem {
public:
    const sf::Texture* TextureType(std::vector<sf::Texture*> a_textures) const override;
    void PaddleCollide(int &a_live, size_t &a_score) const override;
    float GetDeltaVelocity() const override;
    GemType GemTypeType() const override;

private:
    float m_deltaVelocity = 0.75f;
};

#endif