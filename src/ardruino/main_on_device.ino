// OLED_I2C_NumberFonts
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/

#include <OLED_I2C.h>
#include "gaming_functions.h"
#include "display_params.h"
#include "visualization_on_device.h"

extern OLED myOLED;

int matrix[2][2];

void setup()
{
  pinMode(A2, INPUT);
  pinMode(A7, INPUT);
  myOLED.begin();
  visualization_line(); // визуализируем стоблцы, строки и подписи
  create_matrix_for_game(matrix); // создаем матрицу
  visualization_matrix(matrix); // визуализируем матрицу
  myOLED.update();
}

int game_sum = 0; // игровой счет
int total_effect = 0; // итоговый эффект
int counter_steps = 0; // счетчик раундов
int num_round = 5; // количество раундов

//ищем седловую точку 
int saddleRow;
int saddleCol;
int saddleValue;
bool saddlePoint = findSaddlePoint(matrix, saddleRow, saddleCol, saddleValue);

// игровой процесс
void game_process(){
  delay(5000); // задержка 5 секунд
  
  float pA = analogRead(A2)/float(1024); // подаваемые вероятности с потенциометров
  float pB = analogRead(A7)/float(1024);
  float ideal_row_probability = 0.0; // создаем переменные для идеальных вероятностей
  float ideal_column_probability = 0.0;
  
  if (counter_steps == num_round){
    total_effect = total_effect/num_round;
    end_game(); //функция завершения игры
    while(true){
    }
  }
  
  // счет
  game_sum = game_sum + one_round(pA, pB, matrix); 
  
  //задаем значения которые должны были получится для идеальной стратегии
  if(saddlePoint){
    ideal_row_probability = saddleRow;
    ideal_column_probability = saddleCol;
  }else{
    Probabilities ideal_probabilities = ideal_probabilities_for_mixed_strategy(matrix);
    ideal_row_probability = ideal_probabilities.q;
    ideal_column_probability = ideal_probabilities.p;
  }

  int effect = probability_selection_efficiency(ideal_row_probability,ideal_column_probability, pA, pB);// эффект
  total_effect = total_effect + effect;// итоговый эффект
  
  clear_score(); // чистим область для счета
  print_score(game_sum); // визуализация счета

  clear_effect(); // чистим область для эффекта
  print_effect(effect); // визуализация эффекта
  counter_steps++; //счетчик раундов
  myOLED.update();
}

// конец игры
void end_game(){
  clear_effect();
  print_effect(total_effect, 1);
  myOLED.update();
}

void loop()
{
  game_process();
}
