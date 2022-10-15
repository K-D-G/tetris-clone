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

  //Top to bottom
  for(int i=0; i<map.size(); i++){
    map[i]=std::string(WIDTH_BLOCKS, ' ');
  }

  current_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, -5*BLOCK_SIZE);
  next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, -5*BLOCK_SIZE);
}

int Game::start(){
  if(!font.loadFromFile("NotoSansMono-Bold.ttf")){
    std::cerr<<"Error loading font!"<<std::endl;
    return -1;
  }
  score_text.setFont(font);
  score_text.setCharacterSize(48);
  score_text.setFillColor(sf::Color::White);
  score_text.setStyle(sf::Text::Bold);
  score_text.setString("Score: 0");
  score_text.setPosition(sf::Vector2f(0.0f, 0.0f));

  score=0;
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

    int* current_location=current_piece.get_block_position();
    std::string& current_piece_map=current_piece.get_piece_map();
    for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
        //Calculate change that will be made in the update line
        //Evaluate if it collides
        //If it does stop it, check for line completion and game over, get new piece
        //and update score
      }
    }
    score_text.setString("Score: "+std::to_string(score));

    current_piece.update(dt, ((fast_fall)?PRESSED_FALL_SPEED:FALL_SPEED));

    window.clear();
    current_piece.draw(window);
    window.draw(score_text);
    window.display();
  }
  return 0;
}
