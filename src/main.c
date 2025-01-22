#include "brick_game/tetris/tetris_backend.h"
#include "gui/cli/tetris_frontend.h"

/**
 * @brief Точка входа в программу. Вызов функции запуска игры.
 *
 * @return int Статус выхода программы (0 - успех, 1 - ошибка).
 */
int main() {
  srand((unsigned)time(NULL));
  int flag = start();
  return flag;
}