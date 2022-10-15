#ifndef TETRIS__UTILS_H
#define TETRIS__UTILS_H

#define TITLE "TETRIS"
#define BLOCK_SIZE 40.0f
#define BLOCK_OUTLINE_THICKNESS 4
#define WIDTH_BLOCKS 20
#define HEIGHT_BLOCKS 30
#define WIDTH BLOCK_SIZE*WIDTH_BLOCKS
#define HEIGHT BLOCK_SIZE*HEIGHT_BLOCKS
#define FALL_SPEED 2.0f // blocks/s
#define PRESSED_FALL_SPEED 8.0f //blocks/s means when key is pressed will fall at 5 as we summing both non pressed and pressed

#include <cstdlib>
#include <cmath>

namespace Tetris{
  int random(int start, int stop);
}
#endif
