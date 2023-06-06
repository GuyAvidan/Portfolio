#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "objectGame.hpp"
#include "level.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "text.hpp"
#include "resManager.hpp"

class Game
{
public:
    Game(sf::Vector2u a_windowSize, std::string const& a_title, std::string const& a_playerName);
    ~Game();
    void Run();

private:
    void ProcessInput();
    void Update();
    void Draw();
    void CheckBrickCollisions();
    void CheckWallCollisions();
    void CheckPaddleCollisions();
    void CheckGameOver();
    void RestartLevel();
    void LoadLevel();
    void CreateBricks();
    float CalculateScore();

private:
    sf::RenderWindow m_window;
    std::vector<AbstractBrick*> m_bricks;
    Paddle m_paddle;
    Ball m_ball;
    Text m_scoreText;
    Text m_levelText;
    Text m_livesText;
    Text m_gameOverText;
    int m_lives;
    int m_currentLevel;
    size_t m_score;
    bool m_gameOver;
    bool m_ballisStart;
    float m_nx_speed;
    float m_ny_speed;
    float m_nx;
    float m_ny;
    sf::Font m_font;
    sf::Clock m_gameClock;
    size_t m_bricksRemaining;
    sf::Sound m_hitSound;
    sf::Sprite m_background;
    std::string m_playerName;
    sf::RectangleShape m_exploding;
    bool m_exploded;
    sf::Vector2f m_LastBallPosition;
    ResManager m_resManager;
};

#endif // GAME_HPP
