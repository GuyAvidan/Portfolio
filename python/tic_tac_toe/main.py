def create_board(_dimension):
    """This function initializes the game board
        :arg _dimension - the dimension of the board"""
    matrix_init = [["-"] * _dimension for i in range(_dimension)]
    return matrix_init


def display_board(_board, _dimension):
    """This function display the game board
        :arg _board the matrix game board
        :arg _dimension the dimension of the board"""
    for x in _board:
        for i in range(0, _dimension):
            if i == _dimension-1:
                print(" ", x[i])
                print("_"*_dimension*5)
            else:
                print(" ", x[i], end=" |")


def is_legal_move(_board, _x, _y, _dimension, _real):
    """This function checks if the move is legal
            :arg _board the matrix game board
            :arg _dimension the dimension of the board
            :arg _x x cord
            :arg _y y cord
            :arg _real if virtual or real player
            :returns True if it's legal and False if not"""
    if _x >= _dimension or _y >= _dimension:
        print("Coordinates are out of bounds")
        return False
    if _board[_y][_x] != "-":
        if _real:
            print("This cube is already occupied")
        return False
    return True


def enter_turn(_board, _player_sign, _dimension):
    """This function ask the player for coordinate and place his sign on the board
            :arg _board the matrix game board
            :arg _dimension the dimension of the board
            :arg _player_sign the player sign
            """
    try:
        keep_going = True
        while keep_going:
            x = int(input("Please enter X coordinate:"))
            y = int(input("Please enter Y coordinate:"))
            if type(x) is not int or type(x) is not int:
                raise TypeError("x and y must be int")
            if x >= _dimension or y >= _dimension:
                raise IndexError("x and y smaller then", _dimension)
            if not is_legal_move(_board, x, y, _dimension, True):
                keep_going = True
                continue
            _board[y][x] = _player_sign
            keep_going = False
    except Exception as e:
        print("Error:", e)
        enter_turn(_board, _player_sign, _dimension)



def is_winner(_board, _dimension):
    """This function ask the player for coordinate and place his sign on the board
        :arg _board the matrix game board
        :arg _dimension the dimension of the board
        :returns True if there is a winner False if not
        """
    # rows
    for row in _board:
        winner_check = True
        last = row[0]
        for i in range(1, _dimension):
            if row[i] != last or row[i] == "-":
                winner_check = False
        if winner_check:
            return winner_check
    winner_check = True
    # column
    for i in range(0, _dimension):
        last = _board[0][i]
        for j in range(1, _dimension):
            if _board[j][i] != last or _board[j][i] == "-":
                winner_check = False
                break
            else:
                winner_check = True
        if winner_check:
            return winner_check
    winner_check = True
    # diagonal\
    for i in range(0, _dimension-1):
        last = _board[i][i]
        if last == "-" or _board[i + 1][i + 1] != last:
            winner_check = False
    if winner_check:
        return winner_check
    winner_check = True
    # diagonal/
    for i in range(0, _dimension - 1):
        last = _board[_dimension - i - 1][i]
        if last == "-" or _board[_dimension - i - 2][i+1] != last:
            winner_check = False
    if winner_check:
        return winner_check
    return winner_check


def is_full_board(_board, _dimension):
    """This function checks if the board is full
        :arg _board the matrix game board
        :arg _dimension the dimension of the board
        :returns True if it is full False if not
        """
    for row in _board:
        for i in range(0, _dimension):
            if row[i] == "-":
                return False
    return True


def win_move(_board, _dimension, _player_sign):
    """This function checks if there is winning move
        :arg _board the matrix game board
        :arg _dimension the dimension of the board
        :arg _player_sign the player sign
        :returns x, y cord if there is or the dimension if not
        """
    for y in range(0, _dimension):
        for x in range(0, _dimension):
            if is_legal_move(_board, x, y, _dimension, False):
                _board[y][x] = _player_sign
                winner_chance = is_winner(_board, _dimension)
                _board[y][x] = "-"
                if winner_chance:
                    return x, y
    return _dimension, _dimension


def empty_line(_board, _dimension, _virtual_player_sign):
    """This function checks if there is empty line
        :arg _board the matrix game board
        :arg _dimension the dimension of the board
        :arg _virtual_player_sign virtual player sign
        :returns x, y cord if there is or the dimension if not
        """
    x = _dimension
    y = _dimension
    for y in range(0, _dimension):
        empty_check = True
        for x in range(0, _dimension):
            if _board[y][x] != "-" or _board[y][x] != _virtual_player_sign:
                empty_check = False
                break
        if empty_check:
            return x, y
    for x in range(0, _dimension):
        empty_check = True
        for y in range(0, _dimension):
            if _board[y][x] != "-" or _board[y][x] != _virtual_player_sign:
                empty_check = False
                break
        if empty_check:
            return x, y
    return _dimension, _dimension


def empty_space(_board, _dimension):
    for i in range(0, _dimension):
        for j in range(0, _dimension):
            if _board[i][j] == "-":
                return j, i
    return _dimension, _dimension


def mid_space(_board, _dimension):
    if _board[_dimension//2][_dimension//2] == "-":
        return _dimension//2, _dimension//2
    return _dimension, _dimension


def virtual_player(_board, _virtual_player_sign, _player_sign, _dimension):
    """This function checks the board and return x,y move
        :arg _board the matrix game board
        :arg _dimension the dimension of the board
        :arg _virtual_player_sign the sign of the virtual player
        :arg _player_sign the sign of the player
        """
    x, y = win_move(_board, _dimension, _virtual_player_sign)
    if x < _dimension:
        _board[y][x] = _virtual_player_sign
        # print("win_move1", x, y)
        return
    x, y = win_move(_board, _dimension, _player_sign)
    if x < _dimension:
        _board[y][x] = _virtual_player_sign
        # print("win_move2", x, y)
        return
    x, y = mid_space(_board, _dimension)
    if x < _dimension:
        _board[y][x] = _virtual_player_sign
        # print("mid", x, y)
        return
    x, y = empty_line(_board, _dimension, _virtual_player_sign)
    if x < _dimension:
        _board[y][x] = _virtual_player_sign
        # print("empty line", x, y)
        return
    x, y = empty_space(_board, _dimension)
    _board[y][x] = _virtual_player_sign


if __name__ == '__main__':
    dimension = 3
    winner = False
    full_board = False
    win_sign = ""
    virtual_player_sign = "X"
    player_sign = "O"
    matrix_tic = create_board(dimension)
    # matrix_tic =[["X", "X", "O"], ["O", "X", "O"], ["O", "X", "-"]]
    display_board(matrix_tic, dimension)
    while True:
        print("player '", player_sign, "' turn:")
        enter_turn(matrix_tic, player_sign, dimension)
        display_board(matrix_tic, dimension)
        winner = is_winner(matrix_tic, dimension)
        full_board = is_full_board(matrix_tic, dimension)
        if winner:
            win_sign = player_sign
            break
        if full_board:
            break
        print("virtual player", virtual_player_sign, "turn:")
        virtual_player(matrix_tic, virtual_player_sign, player_sign, dimension)
        display_board(matrix_tic, dimension)
        winner = is_winner(matrix_tic, dimension)
        full_board = is_full_board(matrix_tic, dimension)
        if winner:
            win_sign = virtual_player_sign
            break
        if full_board:
            break
    if winner:
        print('The winner is "', win_sign, '"')
    else:
        print("No winner,Game Over")
