#ifndef LIVE_GEM_HPP
#define LIVE_GEM_HPP

#include <SFML/Graphics.hpp>

#include "abstractGem.hpp"

class LiveGem : public AbstractGem {
public:
    const sf::Texture* TextureType(std::vector<sf::Texture*> a_textures) const override;
    void PaddleCollide(int &a_live, size_t &a_score) const override;
    float GetDeltaVelocity() const override;
    GemType GemTypeType() const override;

private:
    float m_deltaVelocity = 2.0f;
};

#endif
