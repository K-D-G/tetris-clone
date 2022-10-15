#include <tetris/game.h>

using namespace Tetris;

Game::Game(sf::RenderWindow& win):window(win), current_piece(), next_piece(), fast_fall(false), collision(false), game_over(false){
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
  map.reserve(HEIGHT_BLOCKS);
  for(int i=0; i<HEIGHT_BLOCKS; i++){
    map.push_back(std::string(WIDTH_BLOCKS, ' '));
  }

  current_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);
  next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);

  block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
  block.setOutlineThickness(BLOCK_OUTLINE_THICKNESS);
  block.setOutlineColor(sf::Color::Black);
  block.setFillColor(sf::Color(128, 128, 128));//Grey
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

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(48);
  game_over_text.setFillColor(sf::Color::White);
  game_over_text.setStyle(sf::Text::Bold);
  game_over_text.setString("GAME OVER");
  game_over_text.setOrigin(game_over_text.getLocalBounds().width*0.5, game_over_text.getLocalBounds().height*0.5);
  game_over_text.setPosition(sf::Vector2f(WIDTH*0.5, HEIGHT*0.5));

  score=0;
  time=clock.restart().asSeconds();
  while(window.isOpen()){
    time=clock.getElapsedTime().asSeconds();
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

    update_piece(1);

    int* current_location=current_piece.get_block_position();
    std::string& current_piece_map=current_piece.get_piece_map();
    for(int x=0; x<4; x++){
      for(int y=0; y<4; y++){
        if(current_piece_map[x+y*5]=='X'){
          if(map[current_location[1]+y][current_location[0]+x]=='X'||current_location[1]>HEIGHT_BLOCKS){
            collision=true;
            current_piece.set_position(current_location[0]*BLOCK_SIZE, (current_location[1]-1)*BLOCK_SIZE);
            break;
          }
        }
      }
      if(collision){break;}
    }

    if(collision||current_location[1]+current_piece.get_lowest_point()+2>HEIGHT_BLOCKS){
      current_location=current_piece.get_block_position();
      current_piece_map=current_piece.get_piece_map();
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          if(current_piece_map[x+y*5]=='X'){
            map[current_location[1]+y][current_location[0]+x]='X';
          }
        }
      }

      int complete_lines=0;
      for(int i=map.size(); i>0; i--){
        if(map[i]==std::string(WIDTH_BLOCKS, 'X')){
          complete_lines++;
          map.erase(map.begin()+i);
          map.push_back(std::string(WIDTH_BLOCKS, ' '));
        }
      }
      if(complete_lines>4){complete_lines=4;}
      score+=(200*complete_lines-100);
      if(score<0){score=0;}

      int most_consecutive_spaces=0;
      int consecutive_occurs_at=0;
      int consecutive_spaces=0;
      for(int i=0; i<map[0].length(); i++){
        if(map[0][i]==' '){
          consecutive_spaces++;
        }else if(map[0][i]=='X'){
          most_consecutive_spaces=std::max(most_consecutive_spaces, consecutive_spaces);
          consecutive_spaces=0;
          consecutive_occurs_at=i-most_consecutive_spaces;
        }
      }
      most_consecutive_spaces=std::max(most_consecutive_spaces, consecutive_spaces);
      if(most_consecutive_spaces<current_piece.get_width()){
        game_over=true;
      }

      current_piece=next_piece;
      current_piece.set_position(consecutive_occurs_at, 0);
      next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);

      collision=false;
    }

    score_text.setString("Score: "+std::to_string(score));

    if(game_over){
      score_text.setPosition(WIDTH*0.5, HEIGHT*0.6);
      score_text.setOrigin(score_text.getLocalBounds().width*0.5, score_text.getLocalBounds().height*0.5);
      window.draw(score_text);
      window.draw(game_over_text);
    }else{
      window.clear();
      for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
          if(map[i][j]=='X'){
            block.setPosition(j*BLOCK_SIZE, i*BLOCK_SIZE);
            window.draw(block);
          }
        }
      }
      current_piece.draw(window);
      window.draw(score_text);
    }
    window.display();
  }
  return 0;
}

void Game::update_piece(int direction){
  if(fast_fall==true){
    if(time>0.5f){
      current_piece.update(direction*0.5f, PRESSED_FALL_SPEED);
      time=clock.restart().asSeconds();
    }
  }else{
    if(time>1.0f){
      current_piece.update(direction*1, FALL_SPEED);
      time=clock.restart().asSeconds();
    }
  }
}
