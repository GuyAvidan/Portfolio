#ifndef RES_MANAGER_HPP
#define RES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <vector>
#include <string>
#include <map>

enum class TextureType 
{ FOREST, NORMAl, MID2, HARD, MID4, 
EXPLODING, BONUS, TREE, UNBREAKABLE, 
EXPLOSION, LIVE, SCORE, W_SCORE, 
MINUS_SCORE};

class ResManager
{
public:
    static std::shared_ptr<sf::Texture> Get(TextureType const& name);
    ResManager();

private:
    std::shared_ptr<sf::Texture> GetTexture(TextureType const& name);

private:
    std::map< TextureType , std::shared_ptr<sf::Texture> > m_textures;
};

#endif // RES_MANAGER_HPP