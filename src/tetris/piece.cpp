#include <tetris/piece.h>

using namespace Tetris;

Piece::Piece(){

}

Piece::Piece(std::string _piece_map, sf::Color _colour, float _x, float _y):piece_map(_piece_map), x(_x), y(_y){
  //block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
  //block.setFillColor(_colour);
  sf::RectangleShape block;
  for(int i=0; i<piece_map.length(); i++){
    if(piece_map[i]=='X'){
      block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
      block.setFillColor(_colour);
      blocks.push_back(block);
    }
  }
}

void Piece::draw(sf::RenderWindow& window){
  float localx=x;
  float localy=y;
  int count=0;
  for(int i=0; i<piece_map.length(); i++){
    if(piece_map[i]=='\n'){
      localy+=BLOCK_SIZE;
      localx=x;
      continue;
    }
    if(piece_map[i]=='X'){
      blocks[count].setPosition(localx, localy);
      window.draw(blocks[count]);
      count++;
    }
    localx+=BLOCK_SIZE;
  }
}

void Piece::update(float dt, float fall_speed){
  y+=dt*fall_speed*BLOCK_SIZE;
}

void Piece::move(int direction){
  x+=direction*BLOCK_SIZE;
  if(x+BLOCK_SIZE>WIDTH||x<0){
    x-=direction*BLOCK_SIZE;
  }
}

void Piece::rotate(){
  //To rotate rows become columns
  //So bottom to top becomes left to right
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
}

std::string& Piece::get_piece_map(){
  return piece_map;
}

int* Piece::get_block_position(){
  int* result=new int[2];
  result[0]=static_cast<int>(x/BLOCK_SIZE);
  result[1]=static_cast<int>(y/BLOCK_SIZE);
  return result;
}
