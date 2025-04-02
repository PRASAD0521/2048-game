#include "../includes/game2048.h"

int main()
{
    srand(time(0)); // generate a random number according to time
    game2048 g;
    g.print();
    while (1)
    {
        cout << "Use Arrow Keys to Move\n";
        int b = 0;
        int key = _getch();

        // check for ESC key first
        if (key == 27)
        {
            return 0; // exit the game
        }

        // Check for Arrow keys
        if (key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72: // Up Arrow
                b = g.move(0);
                break;
            case 80: // Down Arrow
                b = g.move(1);
                break;
            case 75: // Left Arrow
                b = g.move(2);
                break;
            case 77: // Right Arrow
                b = g.move(3);
                break;
            default:
                cout << "Invalid input\n";
            }
        }
        if (g.iswon)
        {
            cout << "congrats! you WON the GAME !!! \n";
            return 0;
        }
        if (g.isended)
        {
            cout << "GAME OVER\n";
            break;
        }

        if (b == false)
        {
            cout << "Please enter a valid DIRECTION\n";
        }
        if (b)
        {
            g.print();
        }
    }
}