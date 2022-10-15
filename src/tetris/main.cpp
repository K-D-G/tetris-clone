/**
 * @file main.cpp
 * @brief entry point for the game
 *
 * @author Kieran Grayshon
 * @contact kieran.david.grayshon@gmail.com
 *
*/
#include <SFML/Graphics.hpp>
#include <tetris/game.h>

using namespace Tetris;

int main(){
  //Initialise a window here because of SFML
  //Non-copy enforcement
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
  //Initialise the game and run it
  Game game(window);
  return game.start();
}
