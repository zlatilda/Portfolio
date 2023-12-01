#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

#ifndef GAME_H
#define GAME_H


class game
{
private:
    int board[4][4];
    int** prev_board;
    int score;

    pair<int,int> generate_unocupied_position();
    void add_piece();
    bool can_do_move(int, int, int, int);
    void save_prev_move();

public:
    void new_game();
    void apply_move(int);
    int get_board_value(int, int);
    int get_score();
    void restore_to_prev_move();
    ~game();
};

#endif // GAME_H
