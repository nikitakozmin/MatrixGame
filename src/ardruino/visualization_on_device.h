// VISUALIZATION_ON_DEVICE_H
#ifndef VISUALIZATION_ON_DEVICE_H
#define VISUALIZATION_ON_DEVICE_H
#include <OLED_I2C.h>
#include "display_params.h"

void visualization_line();

void visualization_matrix(int matrix[2][2]);

void clear_score();

void print_score(int game_sum);

void clear_effect();

void print_effect(int effect, int flag=0);

#endif //VISUALIZATION_ON_DEVICE_H