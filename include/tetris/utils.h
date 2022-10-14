#ifndef TETRIS__UTILS_H
#define TETRIS__UTILS_H

#define TITLE "TETRIS"
#define WIDTH 1000
#define HEIGHT 2000
#define BLOCK_SIZE 40.0f
#define FALL_SPEED 2.0f // blocks/s
#define PRESSED_FALL_SPEED 10.0f //blocks/s means when key is pressed will fall at 5 as we summing both non pressed and pressed

#include <cstdlib>
#include <cmath>

namespace Tetris{
  int random(int start, int stop);
}
#endif
