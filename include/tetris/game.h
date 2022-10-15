#ifndef TETRIS__GAME_H
#define TETRIS__GAME_H
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <array>
#include<iostream>

#include <tetris/utils.h>
#include <tetris/piece.h>

namespace Tetris{
  class Game{
  private:
    sf::RenderWindow& window;
    sf::Event event;
    sf::Clock clock;

    sf::Font font;
    sf::Text score_text;
    int score;

    float dt;
    bool fast_fall;

    std::array<std::string, WIDTH_BLOCKS> map;
    Piece current_piece;
    Piece next_piece;

    std::array<std::string, 7> piece_layout;
    std::array<sf::Color, 7> colours;
  public:
    Game(sf::RenderWindow& win);

    int start();
  };
}

#endif
