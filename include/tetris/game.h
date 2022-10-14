#ifndef TETRIS__GAME_H
#define TETRIS__GAME_H
#include <SFML/Graphics.hpp>

#include <tetris/utils.h>

namespace Tetris{
  class Game{
  private:
    sf::RenderWindow& window;
    sf::Event event;
  public:
    Game(sf::RenderWindow& win);

    void start();
  };
}

#endif
