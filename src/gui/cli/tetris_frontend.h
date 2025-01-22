
#define SPEED_RATE 0.125
#define READ_DELAY 50

#include <time.h>

#include "../../brick_game/tetris/tetris_backend.h"

int start();
void draw(Tetris *game);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void initialGamebar();
void initialize_ncurses();
void draw_figure(Tetris *game);
void draw_next(Tetris *game);
void handleInput(Tetris *game);
void init_colors();
void clearField(Tetris *game);