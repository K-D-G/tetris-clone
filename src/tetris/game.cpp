#include <tetris/game.h>

using namespace Tetris;

Game::Game(sf::RenderWindow& win):window(win), current_piece(), next_piece(), fast_fall(false){
  //Designed as 4x4 for easy rotating
  piece_layout[0]=" XX \n XX ";
  piece_layout[1]="X   \nX   \nX   \nX   ";
  piece_layout[2]="  XX\n XX ";
  piece_layout[3]=" XX \n  XX";
  piece_layout[4]="X   \nX   \nXX  ";
  piece_layout[5]=" X  \n X  \nXX  ";
  piece_layout[6]="XXX \n X  ";

  colours[0]=sf::Color::Yellow;
  colours[1]=sf::Color::Cyan;
  colours[2]=sf::Color::Red;
  colours[3]=sf::Color::Green;
  colours[4]=sf::Color::Magenta;
  colours[5]=sf::Color::Blue;
  colours[6]=sf::Color(255, 165, 0); //Orange

  current_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, -5*BLOCK_SIZE);
  next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, -5*BLOCK_SIZE);

}

void Game::start(){
  while(window.isOpen()){
    dt=clock.restart().asSeconds();
    while(window.pollEvent(event)){
      if(event.type==sf::Event::Closed){
        window.close();
      }

      if(event.type==sf::Event::KeyPressed){
        if(event.key.code==sf::Keyboard::Down){
          fast_fall=true;
        }

        if(event.key.code==sf::Keyboard::Left){
          current_piece.move(-1);
        }

        if(event.key.code==sf::Keyboard::Right){
          current_piece.move(1);
        }

        if(event.key.code==sf::Keyboard::R){
          current_piece.rotate();
        }
      }

      if(event.type==sf::Event::KeyReleased){
        if(event.key.code==sf::Keyboard::Down){
          fast_fall=false;
        }
      }
    }
    current_piece.update(dt, ((fast_fall)?PRESSED_FALL_SPEED:FALL_SPEED));
    window.clear();
    current_piece.draw(window);
    window.display();
  }
}
