#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>

class ScoreBoard {
public:
    void UpdateScoreIfHigher(std::string const& a_fileName, size_t const& a_newScore, std::string const& a_playerName);
    void Draw(std::string const& a_fileName, sf::RenderWindow& window);

private:
    std::vector<std::pair<std::string, size_t>> ReadScoresFromFile(std::string const& a_fileName);
    void WriteScoresToFile(std::string const& a_fileName, std::vector<std::pair<std::string, size_t>> const& a_scores);
};

#endif 
