#include "gaming_functions.h"
#include "visualization.h"

int matrix[2][2];

void setup()
{
  pinMode(A2, INPUT);
  pinMode(A7, INPUT);
  start_vis();
  initial_visualization(); // визуализируем стоблцы, строки и подписи
  create_matrix_with_no_saddle_point(matrix); // создаем матрицу
  visualization_matrix(matrix); // визуализируем матрицу
  update_vis();
}

int game_sum = 0; // игровой счет
int total_effect = 0; // итоговый эффект
int counter_steps = 0; // счетчик раундов
int num_round = 5; // количество раундов

// игровой процесс
void game_process(){
  delay(5000); // задержка 5 секунд
  
  if (counter_steps == num_round){
    total_effect = total_effect/num_round;
    end_game(); //функция завершения игры
  }

  float pA = analogRead(A2)/float(1024); // подаваемые вероятности с потенциометров
  float pB = analogRead(A7)/float(1024);
  Probabilities ideal_probabilities = ideal_probabilities_for_mixed_strategy(matrix);
  float ideal_row_probability = ideal_probabilities.q;
  float ideal_column_probability = ideal_probabilities.p;
  
  // счет
  game_sum = game_sum + round(mate_expectation_of_game_matrix(matrix, pA, pB));

  int effect = probability_selection_efficiency(ideal_row_probability, ideal_column_probability, pA, pB);// эффект
  total_effect = total_effect + effect;// итоговый эффект
  
  clear_score(); // чистим область для счета
  print_score(game_sum); // визуализация счета

  clear_effect(); // чистим область для эффекта
  print_effect(effect); // визуализация эффекта
  counter_steps++; //счетчик раундов
  update_vis();
}

// конец игры
void end_game(){
  clear_effect();
  print_effect(total_effect, 1);
  update_vis();
  while(true){}
}

void loop()
{
  game_process();
}
