def game_process(matrix, num_rows=None, num_cols=None, num_moves=3, default_row=None, default_col=None):
    # Заполнение значений по умолчанию
    if num_rows == None:
        num_rows = len(matrix)
    if num_cols == None:
        num_cols = len(matrix[0])
        for i in range(num_rows):
            if len(matrix[i]) != num_cols:
                raise ValueError("The matrix has different row sizes")
    if default_row == None:
        default_row = num_rows//2
    if default_col == None:
        default_col = num_cols//2
    
    if num_rows == 0 or num_cols == 0:
        raise ValueError("The matrix cannot be empty")

    # Проверка значений, выставленных не по умолчанию
    if default_row >= num_rows or 0 > default_row:
        raise ValueError("Incorrect default row")
    if default_col >= num_cols or 0 > default_col:
        raise ValueError("Incorrect default column")
    
    # Берём значения из матрицы num_moves раз
    row = default_row
    col = default_col
    print(f"Row {row} and column {col} are selected (count starting from 0)")
    result_choises = []
    for _ in range(num_moves):
        # Пока не будет введено 'send' предоставляем выбор игрокам \
        # в любом порядке и количестве раз
        while True:
            print("Input 'send' or '{num_player}:{player_line_number (index row or column)}'")
            print("(rows - for player '1', columns - for player '2') Example: 2:0")
            data = input("Your input: ").strip()
            if data == "send":
                break
            parts = data.split(':')
            if len(parts) == 2:
                num_player, player_line_number = parts
                if player_line_number.isdigit():
                    if num_player == "1":
                        row = int(player_line_number)
                        print(f"Row {row} and column {col} are selected")
                    elif num_player == "2":
                        col = int(player_line_number)
                        print(f"Row {row} and column {col} are selected")
                    else:
                        print("Missed 'num_player'")
                else:
                    print("Missed 'player_line_number'")
            else:
                print("Missed ':'")
        result_choises.append(matrix[row][col])
    
    return result_choises
