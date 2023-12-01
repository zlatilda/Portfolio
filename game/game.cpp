#include "game.h"

pair<int,int> game::generate_unocupied_position()
{
    int occupied = 1, line, column;
    while(occupied)
    {
        line = rand()%4;
        column = rand()%4;

        if(board[line][column] == 0)
        {
            occupied = 0;
        }
    }
    return make_pair(line, column);
}

void game::add_piece()
{
    pair<int, int> pos = generate_unocupied_position();
    board[pos.first][pos.second] = 2;
}

void game::new_game()
{
    prev_board = new int*[4];
    for (int i = 0; i < 4; ++i)
        prev_board[i] = new int[4];

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            board[i][j] = 0;
            prev_board[i][j] = 0;
        }
    }

    score = 0;

    add_piece();
}

bool game::can_do_move(int line, int column, int next_line, int next_column)
{
    if(next_line < 0 || next_column < 0 || next_line >=4 || next_column >=4
       || (board[line][column] != board[next_line][next_column] && board[next_line][next_column] != 0))
        return false;

    return true;
}


void game::apply_move(int direction)
{
    save_prev_move();
    cout << "SAVED PREV MOVE \n";

    int dir_line[] = {1, 0, -1, 0};

    int dir_column[] = {0, 1, 0, -1};

    int start_line = 0, start_column = 0, line_step = 1, column_step = 1;
    if(direction == 0)
    {
        start_line = 3;
        line_step = -1;
    }
    if(direction == 1)
    {
        start_column = 3;
        column_step = -1;
    }

    int move_possible, can_add_piece = 0;

    do
    {
        move_possible  = 0;
        for(int i=start_line; i>=0 && i<4; i+=line_step)
        {
            for(int j=start_column; j>=0 && j<4; j += column_step)
            {
                int next_i = i + dir_line[direction], next_j = j + dir_column[direction];

                if(board[i][j] && can_do_move(i, j, next_i, next_j))
                {
                    if(board[next_i][next_j] != 0)
                    {
                        cout << board[i][j] << " + " << board[next_i][next_j] << endl;
                        score += board[i][j] + board[next_i][next_j];
                    }
                    board[next_i][next_j] += board[i][j];
                    board[i][j] = 0;
                    move_possible = can_add_piece = 1;

                }
            }
        }
    }while(move_possible);
    if(can_add_piece)
        add_piece();
}

int game::get_board_value(int i, int j)
{
    return board[i][j];
}

int game::get_score()
{
    return score;
}

void game::save_prev_move()
{
    for(int i=0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            prev_board[i][j] = board[i][j];
        }
    }
}

void game::restore_to_prev_move()
{
     for(int i=0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            board[i][j] = prev_board[i][j];
        }
    }
}

game::~game()
{
    for (int i = 0; i < 4; ++i)
        delete [] prev_board[i];
    delete [] prev_board;
}
