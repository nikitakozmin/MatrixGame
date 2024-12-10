def calculate_proximity_percentage(choices, saddle_value, min_num=-99, max_num=99):
    # проверка на очевидно неправильный ввод
    max_choice = max(choices, default=0)
    min_choice = min(choices, default=0)
    if max_choice > max_num or min_choice < min_num:
        raise ValueError("Incorrectly sent parameters min or max num")
    # проверка на седловую точку
    if saddle_value > max_num or saddle_value < min_num:
        raise ValueError("Incorrectly sent parameter saddle_value")
    # максимальное возможное расстояние    
    max_distance1 = abs(saddle_value - min_num)
    max_distance2 = abs(max_num - saddle_value)
    max_possible_sum = received_sum = 0
    for i in range(len(choices)):
        if choices[i] <= saddle_value:
            max_possible_sum += max_distance1
            received_sum += max_distance1 - abs(choices[i]-saddle_value)
        else:
            max_possible_sum += max_distance2
            received_sum += max_distance2 - abs(choices[i]-saddle_value)
    return (received_sum/max_possible_sum) * 100 
