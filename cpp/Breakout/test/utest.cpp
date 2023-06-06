#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "mu_test.h"

#include "abstractBrick.hpp"
#include "normalBrick.hpp"
#include "hardBrick.hpp"
#include "unbreakableBrick.hpp"
#include "explodingBrick.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "level.hpp"
#include "game.hpp"
#include "score.hpp"

BEGIN_TEST(demo)
    sf::Vector2u windowSize(800, 600);
    std::string windowTitle = "My Game";
    std::string a_playerName;
    std::cout << "Enter player name!\n";
    std::cin >> a_playerName;

    Game game(windowSize, windowTitle, a_playerName);
    game.Run();

    ASSERT_PASS();
END_TEST

TEST_SUITE([Game Tests])
    TEST(demo)
END_SUITE
