#include "../includes/game2048.h"
#include <bits/stdc++.h>
using namespace std;

// a custructor.
game2048::game2048() : grid(4, vector<int>(4, 0))
{
    temp = vector<vector<int>>(4, vector<int>(4, 0));
    randomgenerate_block();
    randomgenerate_block();
}

/*
this is the function that generates 2 and 4 in the empty cells.
*/
void game2048::randomgenerate_block()
{
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 0)
                emptyCells.push_back({i, j});
        }
    }

    if (!emptyCells.empty())
    {
        int randomIndex = rand() % emptyCells.size();
        int i = emptyCells[randomIndex].first;
        int j = emptyCells[randomIndex].second;
        grid[i][j] = (rand() % 2 == 0) ? 2 : 4;
    }
}

/*
this temp array is used to check the previous state to the current state.
this is just for user satisfaction to know a move is not possible.
*/
void game2048::copyarray()
{
    temp = grid;
}

// in this function we actually check the changes from the previous state
bool game2048::altered()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[i][j] != grid[i][j])
                return true;
        }
    }
    return false;
}

/*
this is a functoin that perform the actual movement to the grid.
this moves and merges the same content.
this functin gets a perticular row or column from the move function.
it takes the array in such a way that it always moves the array to the right and
keep the updated array in the same way taken.
*/
void game2048::swipe_right(int nums[])
{
    int i = 3, j = 2;
    while (i > 0)
    {
        while (j >= 0 && nums[j] == 0)
        { // go to first non zero elsment
            j--;
        }
        if (j < 0)
            break; // stop the process
        if (nums[i] == 0)
        { // move the zeros to the left of array
            swap(nums[i], nums[j]);
        }
        else
        {
            if (nums[i] == nums[j])
            { // add them if they are equal
                nums[i] = 2 * nums[i];
                nums[j] = 0;
            }
            i--; // we made changes to the nums[i] so we need to decrement.
            /*
            note: we havent made any changes to i while swapping because after swapping there is a chance
            of merging but after merging there is no chance for remerging.
            for that reason we are only decrementing i after performing a merging operation
            */
            if (i <= j) /*when we are doing i-- there is a chance where i <= j. we need
            to handle that case.*/
            {
                j = i - 1;
            }
        }
    }
}

/* if 2048 was formed in the grid then you won the game*/
bool game2048::is_game_won()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool game2048::move(int dir)
{
    copyarray();
    for (int i = 0; i < 4; i++)
    {
        int nums[4] = {0};
        for (int j = 0; j < 4; j++)
        {
            switch (dir)
            {
            case 0:
                nums[3 - j] = grid[j][i];
                break; // UP
            case 1:
                nums[j] = grid[j][i];
                break; // DOWN
            case 2:
                nums[3 - j] = grid[i][j];
                break; // LEFT
            case 3:
                nums[j] = grid[i][j];
                break; // RIGHT
            }
        }
        swipe_right(nums);
        for (int j = 0; j < 4; j++)
        {
            switch (dir)
            {
            case 0:
                grid[j][i] = nums[3 - j];
                break;
            case 1:
                grid[j][i] = nums[j];
                break;
            case 2:
                grid[i][j] = nums[3 - j];
                break;
            case 3:
                grid[i][j] = nums[j];
                break;
            }
        }
    }
    if (is_game_won())
    {
        iswon = true;
    }
    if (!is_game_over() && altered())
    {
        randomgenerate_block();
        return true;
    }
    else if (is_game_over())
    {
        isended = true;
    }
    return false;
}

void game2048::print()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] != 0)
                cout << grid[i][j] << "  |" << '\t';
            else
                cout << "." << "  |" << '\t';
        }
        cout << '\n';
        cout << "------------------------------" << endl;
    }
}
bool game2048::is_game_over()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 0) // early return of zero found
                return false;
            if (j < 3 && grid[i][j] == grid[i][j + 1])
                return false; // Right
            if (i < 3 && grid[i][j] == grid[i + 1][j])
                return false; // Down
        }
    }
    return true;
}