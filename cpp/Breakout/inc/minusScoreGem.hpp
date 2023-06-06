#ifndef MINUS_SCORE_GEM_HPP
#define MINUS_SCORE_GEM_HPP

#include <SFML/Graphics.hpp>

#include "abstractGem.hpp"

class MinusScoreGem : AbstractGem {
public:
    const sf::Texture* TextureType(std::vector<sf::Texture*> a_textures) const override;
    void PaddleCollide(int &a_live, size_t &a_score) const override;
    float GetDeltaVelocity() const override;
    GemType GemTypeType() const override;
private:
    float m_deltaVelocity = 1.0f;
};

#endif