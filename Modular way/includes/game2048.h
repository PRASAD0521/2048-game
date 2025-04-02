#ifndef GAME2048_H
#define GAME2048_H

#include <vector>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class game2048
{
public:
    vector<vector<int>> grid;
    vector<vector<int>> temp;
    bool isended = 0;
    bool iswon = 0;

    game2048(); // constructor
    void randomgenerate_block(); // to generate 2 or 4 randomly in the available cells
    bool is_game_over(); // returns true if game is over
    void copyarray(); // make a copy of current state
    bool altered(); // returns true if there is a chnage form previous to current state
    void swipe_right(int nums[]); // function to perform swiping and merging
    bool is_game_won(); // retuns true if you reached 2048
    bool move(int dir); // to perform UP, DOWN, LEFT , RIGHT moves
    void print(); // print the grid
};

#endif