/**
 * @file game.h
 * @brief header definition for the main game class which controls game logic
 *
 * @author Kieran Grayshon
 * @contact kieran.david.grayshon@gmail.com
 *
*/
#ifndef TETRIS__GAME_H
#define TETRIS__GAME_H
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <array>
#include <algorithm>
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

    sf::Text game_over_text;
    bool game_over;

    float time;
    bool fast_fall;
    bool collision;

    std::vector<std::string> map;
    Piece current_piece;
    Piece next_piece;

    std::array<std::string, 7> piece_layout;
    std::array<sf::Color, 7> colours;
    sf::RectangleShape block;
  public:
    Game(sf::RenderWindow& win);

    int start();
    void update_piece(int direction);
  };
}

#endif
