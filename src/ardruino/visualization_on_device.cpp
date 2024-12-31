#include "visualization_on_device.h"

OLED myOLED(SDA, SCL, 8);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void visualization_line(){
  myOLED.setFont(SmallFont);
  // отрисовка визуала
  for (int i=0; i<30; i++)
  {
    myOLED.print("-", i*3, horiz_matrix_line_y);
  }
  for (int i=0; i<12; i++)
  {
    myOLED.print("|", vert_matrix_line1_x, i*6);
  }

  for (int i=0; i<12; i++)
  {
    
    myOLED.print("!", vert_matrix_line2_x, i*6);
  }

  for (int i=0; i<13; i++)
  {
    myOLED.print("-", horiz_score_and_effect_line_x + (i*6), horiz_matrix_line_y);
  }
  myOLED.setFont(SmallFont);
  myOLED.print("score", RIGHT, string_score_y);
  myOLED.print("effect", RIGHT, string_effect_y);
}

void visualization_matrix(int matrix[2][2]){
  myOLED.setFont(BigNumbers);
  // числа первого стоблбца
  myOLED.printNumI(matrix[0][0], LEFT, number_first_row_y);
  myOLED.printNumI(matrix[0][1], LEFT, number_second_row_y);
  // числа второго столбца
  myOLED.printNumI(matrix[1][0], number_second_col_x, number_second_row_y);
  myOLED.printNumI(matrix[1][1], number_second_col_x, number_first_row_y);
}

void clear_score(){
  // обновляем область для корректного изображения подаваемых вероятностей
  for (int x = area_score_numbers_x1; x < area_score_numbers_x2; x++){
    for (int y = area_score_numbers_y1; y <= area_score_numbers_y2; y++){
      myOLED.clrPixel(x, y);
    }
  }
}

void print_score(int game_sum){
  // визуализация счета
  if (game_sum < 0){
    myOLED.setFont(SmallFont);
    myOLED.print("-", minus_score_x, minus_score_y);
    // проверяем работу потенциометров
    myOLED.setFont(MediumNumbers);
    myOLED.print(String((-1)*game_sum % 1000), score_x, score_y);   
  }else{
    // проверяем работу потенциометров
    myOLED.setFont(MediumNumbers);
    myOLED.print(String(game_sum), score_x, score_y); 
  }
}

void clear_effect(){
  // очистить старое значение 
  for (int x = area_effect_numbers_x1; x < area_effect_numbers_x2; x++){
    for (int y = area_effect_numbers_y1; y <= area_effect_numbers_y2; y++){
      myOLED.clrPixel(x, y);
    }
  }
}

void print_effect(int effect, int flag=0){
  myOLED.setFont(SmallFont);
  myOLED.print("%", RIGHT, percent_y);
  if (flag == 0){
    myOLED.print("effect", RIGHT, string_effect_y);
  }else{
    myOLED.print("result", RIGHT, string_effect_y);
    
  }
  if (effect < 0){
    myOLED.setFont(SmallFont);
    myOLED.print("-", minus_effect_x, minus_effect_y);
    // проверяем работу потенциометров
    myOLED.setFont(MediumNumbers);
    myOLED.print(String((-1)*(effect)), effect_x, effect_y);   
  }else{
    // проверяем работу потенциометров
    myOLED.setFont(MediumNumbers);
    myOLED.print(String(effect), effect_x,effect_y); 
  }
}
