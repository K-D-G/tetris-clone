/**
 * @file utils.cpp
 * @brief implementation for a specialised random function
 *
 * @author Kieran Grayshon
 * @contact kieran.david.grayshon@gmail.com
 *
*/
#include <tetris/utils.h>

using namespace Tetris;

/**
 * @name random
 * @brief produce a random integer between 2 values
 *
 * @param start-Beginning of the interval
 * @param stop-End of the interval
*/
int Tetris::random(int start, int stop){
  //Standard generalised calculation of a random number
  return std::round(std::rand()%(stop-start)+start);
}
