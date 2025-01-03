#include "visualization_on_wokwi.h"
#include "emulator_display_params.h"
#include <U8g2lib.h>

// Инициализация для дисплея 128x64
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Шрифты
const uint8_t *smallFont = u8g2_font_5x8_mr;  // Маленький шрифт
const uint8_t *mediumFont = u8g2_font_crox2h_tn;  // Средний шрифт
const uint8_t *bigFont = u8g2_font_helvR18_tf;  // Большой шрифт

void initial_visualization(){
  u8g2.setFont(smallFont); 
  for (int i = 0; i < 14; i++) {
    u8g2.setCursor(i * 6, horiz_matrix_line_y);
    u8g2.print("-");
  }

  for (int i = 0; i < 15; i++) {
    u8g2.setCursor(vert_matrix_line1_x, i * 6);
    u8g2.print("|");
  }

  for (int i = 0; i < 15; i++) {
    u8g2.setCursor(vert_matrix_line2_x, i * 6);
    u8g2.print("!");
  }

  for (int i = 0; i < 13; i++) {
    u8g2.setCursor(horiz_score_and_effect_line_x + (i * 3), horiz_score_and_effect_line_y);
    u8g2.print("-");
  }

  u8g2.setFont(smallFont);
  u8g2.setCursor(string_score_x, string_score_y);
  u8g2.print("score");

  u8g2.setFont(smallFont);
  u8g2.setCursor(string_effect_x, string_effect_y);
  u8g2.print("effect");
}

void visualization_matrix(int matrix[2][2]){
  // отображаем матрицу
  u8g2.setFont(bigFont);
  // Числа первого столбца
  u8g2.setCursor(first_num_x, first_num_y);
  u8g2.print(matrix[0][0]);  // Пример числа
  u8g2.setCursor(first_num_x, second_num_y);
  u8g2.print(matrix[1][0]);  // Пример числа
  // Числа второго столбца
  u8g2.setCursor(second_num_x, first_num_y);
  u8g2.print(matrix[0][1]);  // Пример числа
  u8g2.setCursor(second_num_x, second_num_y);
  u8g2.print(matrix[1][1]);  // Пример числа
}

void clear_score(){
  // Обновление области под числом
  for (int x = area_score_numbers_x1; x < area_score_numbers_x2; x++) {
    for (int y = area_score_numbers_y1; y <= area_score_numbers_y2; y++) {
      u8g2.setDrawColor(0);
      u8g2.drawPixel(x, y);
    }
  }
  u8g2.setDrawColor(1);
}

void print_score(int score){
  if (score < 0){
    // Минус при отрицательном числе
    u8g2.setFont(smallFont);
    u8g2.setCursor(minus_score_x, minus_score_y);
    u8g2.print("-");
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(score_x, score_y);
    u8g2.print((score*(-1)));
  }else{
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(score_x, score_y);
    u8g2.print(score);
  }
}

void clear_effect(){
  // Обновление области под числом
  for (int x = area_effect_numbers_x1; x < area_effect_numbers_x2; x++) {
    for (int y = area_effect_numbers_y1; y <= area_effect_numbers_y2; y++) {
      u8g2.setDrawColor(0);
      u8g2.drawPixel(x, y);
    }
  }
  u8g2.setDrawColor(1);
}

void print_effect(int effect, int flag=0){
  u8g2.setFont(smallFont);
  u8g2.setCursor(percent_x, percent_y);
  u8g2.print("%");
  u8g2.setCursor(string_effect_x, string_effect_y);
  if (flag == 0){
    u8g2.print("effect");
  }else{
    u8g2.print("result");
  }
  if (effect < 0){
    // Минус при отрицательном числе
    u8g2.setFont(smallFont);
    u8g2.setCursor(minus_effect_x, minus_effect_y);
    u8g2.print("-");
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(effect_x, effect_y);
    u8g2.print((effect*(-1)));
  }else{
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(effect_x, effect_y);
    u8g2.print(effect);
  }
}

void start_vis(){
  u8g2.begin(); // Инициализация дисплея
}

void update_vis(){
  u8g2.sendBuffer(); // Обновляем экран после отображения матрицы
}
