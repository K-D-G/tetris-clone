#include <tetris/utils.h>

using namespace Tetris;

int Tetris::random(int start, int stop){
  return std::round(std::rand()%(stop-start)+start);
}
