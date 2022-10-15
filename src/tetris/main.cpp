#include <SFML/Graphics.hpp>

#include <tetris/game.h>

using namespace Tetris;

int main(){
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
  Game game(window);
  return game.start();
}
