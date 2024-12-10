def calculate_proximity_percentage(choices, saddle_value, min_num=-99, max_num=99):
    # проверка на очевидно неправильный ввод
    max_choice = max(choices, default=0)
    min_choice = min(choices, default=0)
    if max_choice > max_num or min_choice < min_num:
        raise ValueError("Incorrectly sent parameters min or max num")
    # вычисляем расстояние от седловой точки для каждого выбора
    distances = [abs(choice - saddle_value) for choice in choices]
    # максимальное возможное расстояние
    max_distance = abs(max_num - min_num)
    # среднее расстояние
    avg_distance = sum(distances) / len(distances) if distances else 0
    # вычисляем процент близости
    proximity_percentage = (1 - avg_distance / max_distance) * 100
    return max(0, proximity_percentage)  # Ограничиваем процент от 0 до 100
