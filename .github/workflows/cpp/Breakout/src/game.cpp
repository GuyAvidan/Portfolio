#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <memory>

#include "game.hpp"
#include "abstractBrick.hpp"
#include "normalBrick.hpp"
#include "explodingBrick.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "score.hpp"
#include "bonus.hpp"
#include "resManager.hpp"

Game::Game(sf::Vector2u a_windowSize, std::string const& a_title, std::string const& a_playerName)
: m_window(sf::VideoMode(a_windowSize.x, a_windowSize.y), a_title)
, m_paddle(sf::Vector2f(400, 550), sf::Vector2f(100, 20))
, m_ball(sf::Vector2f(400, 500), sf::Vector2f(2, -2), sf::Color::Red, 10.f)
, m_lives(3)
, m_currentLevel(1)
, m_score(0)
, m_gameOver(false)
, m_ballisStart(false)
, m_nx_speed(0.0f)
, m_ny_speed(0.0f)
, m_nx(400)
, m_ny(530)
, m_font()
, m_gameClock()
, m_playerName(a_playerName)
, m_exploded(false)
, m_LastBallPosition(sf::Vector2f(400, 550))
, m_resManager()
{
    m_paddle.SetPosition(sf::Vector2f(a_windowSize.x / 2 - m_paddle.GetSizeX() / 2, a_windowSize.y - 50));
    m_ball.SetPosition(sf::Vector2f(m_paddle.GetPosX() + m_paddle.GetSizeX() / 2 - m_ball.GetRadius(), m_paddle.GetPosY() - m_paddle.GetSizeY()));

    m_window.setFramerateLimit(60);
    if(!m_font.loadFromFile("../res/RobotoMono-VariableFont_wght.ttf"))
    {
        std::cerr << "Error loading font\n";
    }
    m_scoreText = Text("Score: 0", m_font, 24, sf::Vector2f(10.0f, 10.0f), sf::Color::White);
    m_levelText = Text("Level: 1", m_font, 24, sf::Vector2f(200.0f, 10.0f), sf::Color::White);
    m_livesText = Text("Lives: 3", m_font, 24, sf::Vector2f(400.0f, 10.0f), sf::Color::White);
    m_gameOverText = Text("Game Over!", m_font, 24, sf::Vector2f(a_windowSize.x / 2 - 100, a_windowSize.y / 2), sf::Color::Red);
    sf::SoundBuffer* bufferS = new sf::SoundBuffer;
    bufferS->loadFromFile("../res/pong.wav");
    //std::shared_ptr<sf::SoundBuffer> bufferSUni(bufferS);
    if(!bufferS->loadFromFile("../res/pong.wav"))
    {
        std::cerr << "Error loading sound\n";
    }
    //m_hitSound.setBuffer(*bufferSUni.get());
    m_hitSound.setBuffer(*bufferS);
    LoadLevel();
    m_bricksRemaining =  m_bricks.size();

    m_background.setTexture(*m_resManager.Get(TextureType::FOREST));
    m_paddle.SetTexture(m_resManager.Get(TextureType::TREE).get());
    m_exploding.setTexture(m_resManager.Get(TextureType::EXPLOSION).get());
    m_exploding.setSize(sf::Vector2f(300, 100));
    m_exploding.setOrigin(m_exploding.getSize().x / 2.f, m_exploding.getSize().y / 2.f);
    m_bonus = Bonus(m_window);
}

Game::~Game()
{
}

void Game::Run()
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("../res/back.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    while(m_window.isOpen())
    {
        ProcessInput();

        Update();

        Draw();

        m_gameClock.restart();
    }
}

void Game::ProcessInput()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }

        if(!m_gameOver) {
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Left) {
                    if (m_paddle.GetPosX() > 0) {
                        m_paddle.Update(-15.0f);
                        if(!m_ballisStart) {
                            m_ball.Update(-15.0f);
                            m_nx -= 15.0f;
                        }
                    }
                } else if(event.key.code == sf::Keyboard::Right) {
                    if (m_paddle.GetPosX() <= m_window.getSize().x - m_paddle.GetSizeX()) {
                        m_paddle.Update(15.0f);
                        if(!m_ballisStart) {
                            m_ball.Update(15.0f);
                            m_nx += 15.0f;
                        }
                    }
                } else if(event.key.code == sf::Keyboard::Up && m_nx_speed == 0.0f) {
                    m_ballisStart = true;
                    m_nx_speed = 3.1f;
                    m_ny_speed = -3.1f;
                }
            }
        }
    }
}

void Game::Update()
{
    if(!m_bonus.IsDone())
    {
        m_bonus.RunBonus(m_lives, m_score, m_paddle);
        m_bonus.Draw();
        
    } 
    CheckWallCollisions();
    CheckBrickCollisions();
    CheckPaddleCollisions();
    m_LastBallPosition = m_ball.GetPosition();

    CheckGameOver();

    bool flag = true;

    for(auto& brick : m_bricks) {
        if(brick->BrickTypeType() != BrickType::UNBREAKABLE) {
            flag = false;
        }
    }

    if (flag)
    {
        /* if (!m_bonus.IsDone())
        {
            m_bonus.RunBonus(m_lives, m_score, m_paddle);
            m_bonus.Draw();
            
        } else { */
            ++m_currentLevel;
            m_lives += 3;
            if(m_currentLevel < 5) {
                LoadLevel();
                RestartLevel();
            } else {
                m_gameOver = true;
                m_gameOverText.SetString("You Won!");
            }

        //}
        
    }
        
        
}


void Game::Draw()
{
    static bool flag = true;
    static int count = 0;

    m_window.clear(sf::Color::Black);
    if(m_gameOver) {
        m_gameOverText.Draw(m_window);

        ScoreBoard score;

        if(flag && m_score > 0) {
            score.UpdateScoreIfHigher("score_board.txt", m_score, m_playerName);
            flag = false;
        }

        score.Draw("score_board.txt" ,m_window);

    } else {
        m_window.draw(m_background);
        m_ball.Draw(m_window);
        m_paddle.Draw(m_window);
        for (auto &brick : m_bricks)
        {
            brick->Draw(m_window);
        }
        if(m_exploded)
        {
            ++count;
            m_window.draw(m_exploding);
            if(count == 20){
                m_exploded = false;
                count = 0;
            }
        }
        m_scoreText.SetString("Score: " + std::to_string(m_score));
        m_levelText.SetString("Level: " + std::to_string(m_currentLevel));
        m_livesText.SetString("Lives: " + std::to_string(m_lives));
        m_scoreText.Draw(m_window);
        m_levelText.Draw(m_window);
        m_livesText.Draw(m_window);
        m_bonus.Draw();
        
    }

    m_window.display();
}

void Game::CheckGameOver()
{
    if(m_lives <= 0)
    {
        m_gameOver = true;
    }
}

void Game::LoadLevel()
{
    Level level;

    m_bricks = level.RunLevel("level_" + std::to_string(m_currentLevel) + ".txt", m_resManager);
}

void Game::CheckBrickCollisions()
{
    for (auto& brick : m_bricks) {
        bool flag = false;

        if(brick->Intersect(m_ball.Right()) || brick->Intersect(m_ball.Left())) {
            flag = true;
            m_nx_speed *= -1;
        } else if(brick->Intersect(m_ball.Top()) || brick->Intersect(m_ball.Bottom())) {
            flag = true;
            m_ny_speed *= -1;
        } 

        if(flag && brick->BrickTypeType() != BrickType::UNBREAKABLE) {
            brick->SetHits(brick->GetHits() - 1, m_resManager);
            m_ball.SetPosition(m_LastBallPosition);
            if(brick->ToDelete()) {
                if(brick->BrickTypeType() == BrickType::EXPLODING) {
                    int exploding = brick->Explode(m_exploding, brick->GetPosition(),m_bricks,m_resManager);
                    m_bricksRemaining -= exploding;
                    m_exploded = true;

                } else {
                    if(brick->BrickTypeType() == BrickType::BONUS) {
                        ++m_lives;
                    } 
                    --m_bricksRemaining;
                }
                m_hitSound.play();
                m_score += CalculateScore();
                m_scoreText.SetString("Score: " + std::to_string(m_score));
            }
        }
    }

    // Remove any bricks that have been marked for deletion
    m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(),
                    [](auto &brick) {
                        if(brick->ToDelete()) {
                            delete brick;
                            brick = nullptr;
                            return true;
                        }
                        return false; 
                    }), m_bricks.end());
}

void Game::CheckWallCollisions()
{
    if (m_ballisStart == true)
    {
        m_nx += m_nx_speed;
        m_ny += m_ny_speed;
        if (m_nx <= 0 + m_ball.GetRadius() || m_window.getSize().x - m_ball.GetRadius() <= m_nx)
        {
            m_nx_speed *= -1;
        }
        if (m_ny <= 0 + m_ball.GetRadius() || m_window.getSize().y - m_ball.GetRadius() <= m_ny)
        {
            m_ny_speed *= -1;
        }
        m_ball.SetPosition(sf::Vector2f(m_nx, m_ny));
    }

    if ((m_ball.Bottom().y >= m_window.getSize().y) && m_playerName != "guy" && m_playerName != "yakov") {
        m_lives--;

        if(m_lives > 0) {
            RestartLevel();
        } else {
            m_gameOver = true;
        }
    }
}

void Game::CheckPaddleCollisions()
{
    if(m_ballisStart == true) {
        if(m_paddle.Intersect(m_ball.Right()) || m_paddle.Intersect(m_ball.Left())) {
            m_nx_speed *= -1;
            m_ball.SetPosition(m_LastBallPosition);

        } else if(m_paddle.Intersect(m_ball.Bottom())) {
            m_ny_speed *= -1;
            m_ball.SetPosition(m_LastBallPosition);
        }
        
    }
}

void Game::RestartLevel()
{
    m_paddle.SetPosition(sf::Vector2f(m_window.getSize().x / 2 - m_paddle.GetSizeX() / 2, m_window.getSize().y - 50));
    m_ball.SetPosition(sf::Vector2f(m_paddle.GetPosX() + m_paddle.GetSizeX() / 2 - m_ball.GetRadius(), m_paddle.GetPosY() - m_paddle.GetSizeY()));

    m_gameOver = false;
    m_ballisStart = false;
    m_nx_speed = 0.0f;
    m_ny_speed = 0.0f;
    m_nx = 400;
    m_ny = 530;
    m_bricksRemaining = m_bricks.size();
}

float Game::CalculateScore()
{
    sf::Time elapsedTime = m_gameClock.getElapsedTime();
    float elapsedTimeInSeconds = elapsedTime.asSeconds();

    float score = 100.0f * (1.0f - (static_cast<float>(m_bricksRemaining) / m_bricks.size()))
        * (1.0f - (elapsedTimeInSeconds / 60.0f));
    return score;
}
