#ifndef TETRIS__PIECE_H
#define TETRIS__PIECE_H
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <tetris/utils.h>

namespace Tetris{
  class Piece{
    std::string piece_map;
    //sf::RectangleShape block;
    std::vector<sf::RectangleShape> blocks;
    float x, y;
    int width;
    int lowest_point;

    void calculate_width();
  public:
    Piece();
    Piece(std::string _piece_map, sf::Color _colour, float _x, float _y);

    void draw(sf::RenderWindow& window);
    void update(float dt, float fall_speed);
    void move(int direction);
    void rotate(); //90 degrees clockwise

    std::string& get_piece_map();
    int* get_block_position();
    int get_width();
    int get_lowest_point();
    void set_position(float _x, float _y);
  };
}


#endif
