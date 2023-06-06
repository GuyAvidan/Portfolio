#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include "resManager.hpp"

ResManager::ResManager()
{
    sf::Texture* buffer0 = new sf::Texture;
    buffer0->loadFromFile("../res/forest.jpg");
    std::shared_ptr<sf::Texture> buf0(buffer0);
    m_textures[TextureType::FOREST] = std::move(buf0);
    sf::Texture* buffer1 = new sf::Texture;
    buffer1->loadFromFile("../res/pink.png");
    std::shared_ptr<sf::Texture> buf1(buffer1);
    m_textures[TextureType::NORMAl] = std::move(buf1);
    sf::Texture* buffer2 = new sf::Texture;
    buffer2->loadFromFile("../res/red.png");
    std::shared_ptr<sf::Texture> buf2(buffer2);
    m_textures[TextureType::MID2] = std::move(buf2);
    sf::Texture* buffer3 = new sf::Texture;
    buffer3->loadFromFile("../res/yellow.png");
    std::shared_ptr<sf::Texture> buf3(buffer3);
    m_textures[TextureType::HARD] = std::move(buf3);
    sf::Texture* buffer4 = new sf::Texture;
    buffer4->loadFromFile("../res/blue.png");
    std::shared_ptr<sf::Texture> buf4(buffer4);
    m_textures[TextureType::MID4] = std::move(buf4);
    sf::Texture* buffer5 = new sf::Texture;
    buffer5->loadFromFile("../res/purple.png");
    std::shared_ptr<sf::Texture> buf5(buffer5);
    m_textures[TextureType::EXPLODING] = std::move(buf5);
    sf::Texture* buffer6 = new sf::Texture;
    buffer6->loadFromFile("../res/bonus.png");
    std::shared_ptr<sf::Texture> buf6(buffer6);
    m_textures[TextureType::BONUS] = std::move(buf6);
    sf::Texture* buffer7 = new sf::Texture;
    buffer7->loadFromFile("../res/tree.png");
    std::shared_ptr<sf::Texture> buf7(buffer7);
    m_textures[TextureType::TREE] = std::move(buf7);
    sf::Texture* buffer8 = new sf::Texture;
    buffer8->loadFromFile("../res/silver.png");
    std::shared_ptr<sf::Texture> buf8(buffer8);
    m_textures[TextureType::UNBREAKABLE] = std::move(buf8);
    sf::Texture* buffer9 = new sf::Texture;
    buffer9->loadFromFile("../res/expld.png");
    std::shared_ptr<sf::Texture> buf9(buffer9);
    m_textures[TextureType::EXPLOSION] = std::move(buf9);
    sf::Texture* buffer10 = new sf::Texture;
    buffer10->loadFromFile("../res/liveGem.png");
    std::shared_ptr<sf::Texture> buf10(buffer10);
    m_textures[TextureType::LIVE] = std::move(buf10);
    sf::Texture* buffer11 = new sf::Texture;
    buffer11->loadFromFile("../res/scoreGem.png");
    std::shared_ptr<sf::Texture> buf11(buffer11);
    m_textures[TextureType::SCORE] = std::move(buf11);
    sf::Texture* buffer12 = new sf::Texture;
    buffer12->loadFromFile("../res/wScoreGem.png");
    std::shared_ptr<sf::Texture> buf12(buffer12);
    m_textures[TextureType::W_SCORE] = std::move(buf12);
    sf::Texture* buffer13 = new sf::Texture;
    buffer13->loadFromFile("../res/minusScoreGem.png");
    std::shared_ptr<sf::Texture> buf13(buffer13);
    m_textures[TextureType::MINUS_SCORE] = std::move(buf13);

}

std::shared_ptr<sf::Texture> ResManager::Get(TextureType const& name)
{
    static ResManager rm;
    return rm.GetTexture(name);
}

std::shared_ptr<sf::Texture> ResManager::GetTexture(TextureType const& name)
{
    return m_textures[name];
}

