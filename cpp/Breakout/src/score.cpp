#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "score.hpp"

void ScoreBoard::Draw(std::string const& a_fileName, sf::RenderWindow &a_window) 
{
    sf::Font font;
    if (!font.loadFromFile("../res/RobotoMono-VariableFont_wght.ttf"))
    {
        std::cerr << "Failed to font loadFromFile: " << a_fileName << std::endl;
        return;
    }

    std::vector<std::pair<std::string, size_t>> scores = ReadScoresFromFile(a_fileName);

    std::stringstream table;
    table << "+--------+----------+---------+\n";
    table << "|  Rank  |   Name   |  Score  |\n";
    table << "+--------+----------+---------+\n";

    size_t i = 1;
    for (auto &[name, score] : scores)
    {
        table << "|" << std::setw(8) << i << "|";
        table << std::setw(10) << name << "|";
        table << std::setw(9) << score << "|\n";
        ++i;
    }

    table << "+--------+----------+---------+\n";

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);

    text.setString(table.str());

    a_window.draw(text);
}

void ScoreBoard::UpdateScoreIfHigher(std::string const &a_fileName, size_t const &a_newScore, std::string const &a_playerName)
{
    std::vector<std::pair<std::string, size_t>> scores = ReadScoresFromFile(a_fileName);

    bool a_playerFound = false;
    for (auto &[name, score] : scores)
    {
        if (name == a_playerName)
        {
            a_playerFound = true;

            if (a_newScore > score)
            {
                score = a_newScore;
            }

            break;
        }
    }

    if (!a_playerFound)
    {
        scores.emplace_back(a_playerName, a_newScore);
    }

    std::sort(scores.begin(), scores.end(),
              [](auto &a, auto &b)
              {
                  return a.second > b.second;
              });

    if (scores.size() > 10)
    {
        scores.resize(10);
    }

    WriteScoresToFile(a_fileName, scores);
}

std::vector<std::pair<std::string, size_t>> ScoreBoard::ReadScoresFromFile(std::string const &a_fileName)
{
    std::vector<std::pair<std::string, size_t>> scores;

    std::ifstream file(a_fileName);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name;
            size_t score;
            if (iss >> name >> score)
            {
                scores.emplace_back(name, score);
            }
        }

        file.close();
    }

    return scores;
}

void ScoreBoard::WriteScoresToFile(std::string const &a_fileName, std::vector<std::pair<std::string, size_t>> const &a_scores)
{
    std::ofstream file(a_fileName);
    if (file.is_open())
    {
        file.clear();
        file.seekp(0);

        for (auto &score : a_scores)
        {
            file << score.first << " " << score.second << std::endl;
        }

        file.close();
    }
}
