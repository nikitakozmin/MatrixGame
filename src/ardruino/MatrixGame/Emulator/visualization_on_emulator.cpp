#include "visualization.h"
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
    u8g2.setCursor(i * 6, 33);
    u8g2.print("-");
  }

  for (int i = 0; i < 15; i++) {
    u8g2.setCursor(7 + 76, i * 6);
    u8g2.print("|");
  }

  for (int i = 0; i < 15; i++) {
    u8g2.setCursor(119 / 3, i * 6);
    u8g2.print("!");
  }

  for (int i = 0; i < 13; i++) {
    u8g2.setCursor(2 * 128 / 3 + 2 + (i * 3), 33);
    u8g2.print("-");
  }

  u8g2.setFont(smallFont);
  u8g2.setCursor(2 * 128 / 3 + 10, 7);
  u8g2.print("score");

  u8g2.setFont(smallFont);
  u8g2.setCursor(2 * 128 / 3 + 8, 39);
  u8g2.print("effect");
}

void visualization_matrix(int matrix[2][2]){
  // отображаем матрицу
  u8g2.setFont(bigFont);
  // Числа первого столбца
  u8g2.setCursor(5, 25);
  u8g2.print(matrix[0][0]);  // Пример числа
  u8g2.setCursor(5, 60);
  u8g2.print(matrix[1][0]);  // Пример числа
  // Числа второго столбца
  u8g2.setCursor(132 / 3 + 5, 25);
  u8g2.print(matrix[0][1]);  // Пример числа
  u8g2.setCursor(132 / 3 + 5, 60);
  u8g2.print(matrix[1][1]);  // Пример числа
}

void clear_score(){
  // Обновление области под числом
  for (int x = 92; x < 128; x++) {
    for (int y = 9; y <= 25; y++) {
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
    u8g2.setCursor(2 * 126 / 3 + 5, 20);
    u8g2.print("-");
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(2 * 128 / 3 + 15, 20);
    u8g2.print((score*(-1)));
  }else{
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(2 * 128 / 3 + 15, 20);
    u8g2.print(score);
  }
}

void clear_effect(){
  // Обновление области под числом
  // u8g2.setCursor(2 * 128 / 3 + 8, 39);
  for (int x = 92; x < 128; x++) {
    for (int y = 39; y <= 64; y++) {
      u8g2.setDrawColor(0);
      u8g2.drawPixel(x, y);
    }
  }
  u8g2.setDrawColor(1);
}

void print_effect(int effect, int flag=0){
  u8g2.setFont(smallFont);
  u8g2.setCursor(120, 55);
  u8g2.print("%");
  u8g2.setCursor(2 * 128 / 3 + 8, 39);
  if (flag == 0){
    u8g2.print("effect");
  }else{
    u8g2.print("result");
  }
  if (effect < 0){
    // Минус при отрицательном числе
    u8g2.setFont(smallFont);
    u8g2.setCursor(2 * 128 / 3 + 10, 57);
    u8g2.print("-");
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(2 * 128 / 3 + 10, 55);
    u8g2.print((effect*(-1)));
  }else{
    // Отображение значения счета
    u8g2.setFont(mediumFont);
    u8g2.setCursor(2 * 128 / 3 + 10, 55);
    u8g2.print(effect);
  }
}

void start_vis(){
  u8g2.begin(); // Инициализация дисплея
}

void update_vis(){
  u8g2.sendBuffer(); // Обновляем экран после отображения матрицы
}
