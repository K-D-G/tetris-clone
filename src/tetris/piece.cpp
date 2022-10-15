/**
 * @file piece.cpp
 * @brief implementation for a tetris piece
 *
 * @author Kieran Grayshon
 * @contact kieran.david.grayshon@gmail.com
 *
*/
#include <tetris/piece.h>

using namespace Tetris;

/**
 * @name Piece constructor
 * @brief Default constructor for initialisation of the memory space
*/
Piece::Piece(){

}

/**
 * @name Piece constructor
 * @brief Initialises a tetris piece
 *
 * @param piece map-Layout of the piece
 * @param colour
 * @param x-Part of position component
 * @param y-Part of position component
*/
Piece::Piece(std::string _piece_map, sf::Color _colour, float _x, float _y):piece_map(_piece_map), x(_x), y(_y), width(0){
  //By using the piece map as a template
  //Generate blocks for each point and add them to a vector
  sf::RectangleShape block;
  for(int i=0; i<piece_map.length(); i++){
    if(piece_map[i]=='X'){
      block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
      block.setFillColor(_colour);
      block.setOutlineThickness(BLOCK_OUTLINE_THICKNESS);
      block.setOutlineColor(sf::Color::Black);
      blocks.push_back(block);
    }
  }
  calculate_width();
}

/**
 * @name calculate_width
 * @brief Calculates the maximum width of the piece for
 *        placement
*/
void Piece::calculate_width(){
  //Iterate through each row of the layout
  //The biggest string of X's will be the max width
  //And look for the lowest point (this is not at the bottom due to padding)
  int x_count=0;
  width=0;
  lowest_point=0;
  for(int i=0; i<piece_map.length(); i++){
    if(piece_map[i]=='\n'){
      width=std::max(x_count, width);
      x_count=0;
    }else if(piece_map[i]=='X'){
      x_count++;
      lowest_point=std::max(
        lowest_point,
        static_cast<int>(floor(i/4))
      );
    }
  }
}

/**
 * @name Piece::draw
 * @brief draw's the tetris piece to the window
 *
 * @param window-Window to draw onto
*/
void Piece::draw(sf::RenderWindow& window){
  //Iterate through the template array
  //Then move the blocks into its proper screen position place
  float localx=x;
  float localy=y;
  int count=0;
  for(int i=0; i<piece_map.length(); i++){
    //Move onto next row
    if(piece_map[i]=='\n'){
      localy+=BLOCK_SIZE;
      localx=x;
      continue;
    }
    //Move into position
    if(piece_map[i]=='X'){
      blocks[count].setPosition(localx, localy);
      window.draw(blocks[count]);
      count++;
    }
    localx+=BLOCK_SIZE;
  }
}

/**
 * @name Piece::update
 * @brief update the location of the piece with time and current speed
 *
 * @param dt-Delta Time (time elapsed since last update)
 * @param fall_speed-Rate of fall of the piece in blocks/s
*/
void Piece::update(float dt, float fall_speed){
  //Standard velocity addition using delta time
  y+=dt*fall_speed*BLOCK_SIZE;
}

/**
 * @name move
 * @brief move the piece left or right
 *
 * @param direction- +1 for right -1 for left
*/
void Piece::move(int direction){
  //Move the piece left to right a block
  //Not forgetting to constrain it to the screen
  x+=direction*BLOCK_SIZE;
  if(x+BLOCK_SIZE>WIDTH||x<0){
    x-=direction*BLOCK_SIZE;
  }
}

/**
 * @name Piece::rotate
 * @brief rotates the piece 90 degrees clockwise
*/
void Piece::rotate(){
  //To rotate rows become columns
  //So bottom to top becomes left to right
  //Basically tranposing a matrix
  std::string temp_piece_map="";
  std::string row="";
  for(int x=0; x<4; x++){
    row="";
    for(int i=0; i<4; i++){
      row+=piece_map[x+i*5];
    }
    row+="\n";
    temp_piece_map+=row;
  }
  piece_map=temp_piece_map;
  //Recalculate max width as it could easily have changed
  calculate_width();
}

/**
 * @name Piece::get_piece_map
 * @brief returns piece_map
*/
std::string& Piece::get_piece_map(){
  return piece_map;
}

/**
 * @name Piece::get_block_position
 * @brief returns the location of the top left of the piece
 *        by treating the screen as a grid of squares of BLOCK_SIZE
*/
int* Piece::get_block_position(){
  //Convert the screen position to how "blocks" it is instead
  int* result=new int[2];
  result[0]=static_cast<int>(x/BLOCK_SIZE);
  result[1]=static_cast<int>(y/BLOCK_SIZE);
  return result;
}

/**
 * @name Piece::get_width
 * @brief returns max width of the piece
 *
 * @param
 * @param
*/
int Piece::get_width(){
  return width;
}

/**
 * @name Piece::get_lowest_point
 * @brief returns the lowest relative point of the piece
*/
int Piece::get_lowest_point(){
  return lowest_point;
}

/**
 * @name Piece::set_position
 * @brief sets the screen position of the piece
 *
 * @param x
 * @param y
*/
void Piece::set_position(float _x, float _y){
  x=_x;
  y=_y;
}
