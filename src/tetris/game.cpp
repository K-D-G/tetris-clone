#include <tetris/game.h>

using namespace Tetris;

Game::Game(sf::RenderWindow& win):window(win){

}

void Game::start(){
  while(window.isOpen()){
    while(window.pollEvent(event)){
      if(event.type==sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    window.display();
  }
}
