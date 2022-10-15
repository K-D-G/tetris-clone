/**
 * @file game.cpp
 * @brief implementation of the game with all the logic
 *
 * @author Kieran Grayshon
 * @contact kieran.david.grayshon@gmail.com
 *
*/
#include <tetris/game.h>

using namespace Tetris;


/**
 * @name Game constructor
 * @brief constructs basic game constructs ready for executio
 *
 * @param window-A window to draw things to
*/
Game::Game(sf::RenderWindow& win):window(win), current_piece(), next_piece(), fast_fall(false), collision(false), game_over(false){
  //Designed as 4x4 for easy rotating
  //Layout of the blocks that make up each piece
  piece_layout[0]=" XX \n XX ";
  piece_layout[1]="X   \nX   \nX   \nX   ";
  piece_layout[2]="  XX\n XX ";
  piece_layout[3]=" XX \n  XX";
  piece_layout[4]="X   \nX   \nXX  ";
  piece_layout[5]=" X  \n X  \nXX  ";
  piece_layout[6]="XXX \n X  ";

  //Different colour possibilities
  colours[0]=sf::Color::Yellow;
  colours[1]=sf::Color::Cyan;
  colours[2]=sf::Color::Red;
  colours[3]=sf::Color::Green;
  colours[4]=sf::Color::Magenta;
  colours[5]=sf::Color::Blue;
  colours[6]=sf::Color(255, 165, 0); //Orange

  //Initialise the map
  //Top to bottom
  map.reserve(HEIGHT_BLOCKS);
  for(int i=0; i<HEIGHT_BLOCKS; i++){
    map.push_back(std::string(WIDTH_BLOCKS, ' '));
  }

  //Initialise pieces
  current_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);
  next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);

  //Generate a generic block template to generate the map
  block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
  block.setOutlineThickness(BLOCK_OUTLINE_THICKNESS);
  block.setOutlineColor(sf::Color::Black);
  block.setFillColor(sf::Color(128, 128, 128));//Grey
}

/**
 * @name Game::start
 * @brief Controls all game logic and its execution
*/
int Game::start(){
  //Load the font with error handling
  if(!font.loadFromFile("NotoSansMono-Bold.ttf")){
    std::cerr<<"Error loading font!"<<std::endl;
    return -1;
  }

  //Initialise the 2 text objects
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

  //Set score and clock up
  score=0;
  time=clock.restart().asSeconds();
  while(window.isOpen()){
    //Get the time each frame
    time=clock.getElapsedTime().asSeconds();

    //Basic input polling
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

    //Move the current piece downwards
    update_piece(1);

    //Get a copy of what the piece looks like and where it is
    int* current_location=current_piece.get_block_position();
    std::string& current_piece_map=current_piece.get_piece_map();
    //Nested for loops to check the piece layout
    //And compare it to the map to see if there is a collision
    for(int x=0; x<4; x++){
      for(int y=0; y<4; y++){
        if(current_piece_map[x+y*5]=='X'){
          if(map[current_location[1]+y][current_location[0]+x]=='X'||current_location[1]>HEIGHT_BLOCKS){
            //Set the piece solid in place and set collision flag
            collision=true;
            current_piece.set_position(current_location[0]*BLOCK_SIZE, (current_location[1]-1)*BLOCK_SIZE);
            break;
          }
        }
      }
      //For efficiency reasons
      if(collision){break;}
    }

    //Check if there has been or collision or the piece is going off screen
    if(collision||current_location[1]+current_piece.get_lowest_point()+2>HEIGHT_BLOCKS){
      //Input the data into the map as it is now solid
      current_location=current_piece.get_block_position();
      current_piece_map=current_piece.get_piece_map();
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          if(current_piece_map[x+y*5]=='X'){
            map[current_location[1]+y][current_location[0]+x]='X';
          }
        }
      }

      //Loop through the map checking for complete lines
      //Then erasing them and squashing the map together
      int complete_lines=0;
      for(int i=map.size(); i>0; i--){
        if(map[i]==std::string(WIDTH_BLOCKS, 'X')){
          complete_lines++;
          map.erase(map.begin()+i);
          map.push_back(std::string(WIDTH_BLOCKS, ' '));
        }
      }
      //Calculate the addition to the score
      //100, 300, 500, or 700 depending on how many
      //complete lines in one go
      if(complete_lines>4){complete_lines=4;}
      score+=(200*complete_lines-100);
      if(score<0){score=0;}

      //Find the most amount of consecutive spaces
      //On the top row and record where it is
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

      //Compare the amount of free spaces at the top with the width of the piece
      //If there isn't enough room the game is over
      if(most_consecutive_spaces<current_piece.get_width()){
        game_over=true;
      }

      //Initialise the next piece and set its position at a
      //free spot at the top
      current_piece=next_piece;
      current_piece.set_position(consecutive_occurs_at, 0);
      next_piece=Piece(piece_layout[random(0, 6)], colours[random(0, 6)], WIDTH*0.5f, 0);

      //Just so there is no unecessary repeats
      collision=false;
    }

    //Update the UI score
    score_text.setString("Score: "+std::to_string(score));

    //If the game is over we stop the drawing new data
    //And draw game over information with the score
    if(game_over){
      score_text.setPosition(WIDTH*0.5, HEIGHT*0.6);
      score_text.setOrigin(score_text.getLocalBounds().width*0.5, score_text.getLocalBounds().height*0.5);
      window.draw(score_text);
      window.draw(game_over_text);
    }else{
      //If not clear the screen, draw the map and the current piece
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

/**
 * @name Game::update_piece
 * @brief Used to move the current piece up or down with special
 *        logic for its speed and displaying
 *
 * @param direction-To go up or down +1 for down -1 for up
 * @param
*/
void Game::update_piece(int direction){
  //When the piece is travellling faster
  //We update the display more frequently
  //So it doesn't just look like it's jumping around
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
