#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <tuple>

using namespace std;

const int N = 1;
const int S = 2;
const int E = 4;
const int W = 8;

// End of game flags
bool win = false;
bool lose = false;

// End of session flag
bool done = false;

// User-chosen variables
int numTrolls;
int size;

// Map width (and height)
int width;

// Character position
tuple<int, int> myPos;
// Enemy positions
tuple<int, int> trolls[10];


// Menu navigation
int selection;

// Contains the maze datastructure and the maze that is actually displayed
int maze[20][20];
char charMaze[41][41];

// Allows the player to move
void gameplay();

// Picks a map based on the requested size
void mapGen();

// Causes every troll to move towards the player
void trollMove();

// Updates the display of the game
void printMap();

// Allows menu navigation before the game starts
void menuUpdate();

// Displays the result of the game
void gameOver();

// Displays the main menu
void menu();

// Creates the maze recursively
void mazeCell(int x, int y, int dir);

// Checks for empty adjacent cells
bool emptyAdjacentCells(int x, int y);

// Clears the screen
void clearScreen();

int main() {
    // Create stdscrow
    initscr();

    // Don't display user input
    noecho();

    // Seed RNG
    srand (time(NULL));

    // Allow special character input
    keypad(stdscr, TRUE);

    // Allow color schemes
    start_color();
    // Enemy/You Lose text
    init_pair(1, COLOR_RED, COLOR_BLACK);
    // Target/You Win text
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    // GAME //
    while (!done) {
        // Display menu
        menu();

        // Create map
        mapGen();

        // Play game
        gameplay();

        // Don't display game over screen if quitting
        if (!done)
            gameOver();
    }

    endwin();
    return 0;
}

void gameplay() {
    while(!win && !lose && !done) {
        int ch = getch();
        switch (ch) {
            case 'k':
            case KEY_UP:
                charMaze[get<0>(myPos)][get<1>(myPos)] = ' ';
                if (charMaze[get<0>(myPos)][get<1>(myPos)-1] == 'X')
                    win = true;
                else if (charMaze[get<0>(myPos)][get<1>(myPos)-1] == '#' && charMaze[get<0>(myPos)][get<1>(myPos)-2] == ' ') {
                    charMaze[get<0>(myPos)][get<1>(myPos)-1] = ' ';
                    charMaze[get<0>(myPos)][get<1>(myPos)-2] = '#';
                } 
                if (charMaze[get<0>(myPos)][get<1>(myPos)-1] == ' ') {
                    get<1>(myPos)--;
                }
                charMaze[get<0>(myPos)][get<1>(myPos)] = '^';
                trollMove();
                break;
            case 'j':
            case KEY_DOWN:
                charMaze[get<0>(myPos)][get<1>(myPos)] = ' ';
                if (charMaze[get<0>(myPos)][get<1>(myPos)+1] == 'X')
                    win = true;
                else if (charMaze[get<0>(myPos)][get<1>(myPos)+1] == '#' && charMaze[get<0>(myPos)][get<1>(myPos)+2] == ' ') {
                    charMaze[get<0>(myPos)][get<1>(myPos)+1] = ' ';
                    charMaze[get<0>(myPos)][get<1>(myPos)+2] = '#';
                } 
                if (charMaze[get<0>(myPos)][get<1>(myPos)+1] == ' ') {
                    get<1>(myPos)++;
                }
                charMaze[get<0>(myPos)][get<1>(myPos)] = 'v';
                trollMove();
                break;
            case 'h':
            case KEY_LEFT:
                charMaze[get<0>(myPos)][get<1>(myPos)] = ' ';
                if (charMaze[get<0>(myPos)-1][get<1>(myPos)] == 'X')
                    win = true;
                else if (charMaze[get<0>(myPos)-1][get<1>(myPos)] == '#' && charMaze[get<0>(myPos)-2][get<1>(myPos)] == ' ') {
                    charMaze[get<0>(myPos)-1][get<1>(myPos)] = ' ';
                    charMaze[get<0>(myPos)-2][get<1>(myPos)] = '#';
                } 
                if (charMaze[get<0>(myPos)-1][get<1>(myPos)] == ' ') {
                    get<0>(myPos)--;
                }
                charMaze[get<0>(myPos)][get<1>(myPos)] = '<';
                trollMove();
                break;
            case 'l':
            case KEY_RIGHT:
                charMaze[get<0>(myPos)][get<1>(myPos)] = ' ';
                if (charMaze[get<0>(myPos)+1][get<1>(myPos)] == 'X')
                    win = true;
                else if (charMaze[get<0>(myPos)+1][get<1>(myPos)] == '#' && charMaze[get<0>(myPos)+2][get<1>(myPos)] == ' ') {
                    charMaze[get<0>(myPos)+1][get<1>(myPos)] = ' ';
                    charMaze[get<0>(myPos)+2][get<1>(myPos)] = '#';
                } 
                if (charMaze[get<0>(myPos)+1][get<1>(myPos)] == ' ') {
                    get<0>(myPos)++;
                }
                charMaze[get<0>(myPos)][get<1>(myPos)] = '>';
                trollMove();
                break;
            case 27:        // ESC
                done = true;
                return;
        }

        printMap();
        wmove(stdscr, get<1>(myPos), get<0>(myPos));
    }
}

void mapGen() {
    int x, y;

    // Sets the size of the maze based on the user's selection
    switch (size) {
        case 0:
            width = 10;
            break;
        case 1:
            width = 15;
            break;
        case 2:
            width = 20;
            break;
    }

    // Create the maze data structure
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
            maze[j][i] = 0;

    // Fill the maze with unbroken walls and empty cells
    for (int i = 0; i < width*2+1; i++)
        for (int j = 0; j < width*2+1; j++) {
            charMaze[j][i] = '#';
            if (i%2 == 1 && j%2 == 1)
                charMaze[j][i] = ' ';
        }

    mazeCell(0, 0, 0);

    // Creates maze with characters based on maze data structure
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            if (maze[j][i] & 4) charMaze[2*j+2][2*i+1] = ' ';
            if (maze[j][i] & 2) charMaze[2*j+1][2*i+2] = ' ';
        }
    }
    // Exit Placement //
    do { 
        x = rand() % width*2+1; 
        y = rand() % width*2+1;
    } while (charMaze[x][y] != ' ');
    charMaze[x][y] = 'X';

    // Character Placement //
    do { 
        get<0>(myPos) = rand() % width*2+1; 
        get<1>(myPos) = rand() % width*2+1;
    } while (charMaze[get<0>(myPos)][get<1>(myPos)] != ' ');
    charMaze[get<0>(myPos)][get<1>(myPos)] = '^';

    // Troll Placement //
    for (int i = 0; i < numTrolls; i++) {
        do { 
            get<0>(trolls[i]) = rand() % width*2+1; 
            get<1>(trolls[i]) = rand() % width*2+1;
        } while (charMaze[get<0>(trolls[i])][get<1>(trolls[i])] != ' ');
        charMaze[get<0>(trolls[i])][get<1>(trolls[i])]  = 'T';
    }

    printMap();
    wmove(stdscr, get<1>(myPos), get<0>(myPos));
}

void trollMove() {
    for (int i = 0; i < numTrolls; i++) {
        charMaze[get<0>(trolls[i])][get<1>(trolls[i])] = ' ';

        // Check if troll should move up
        if (get<1>(trolls[i]) > get<1>(myPos) && charMaze[get<0>(trolls[i])][get<1>(trolls[i])-1] == ' ' || get<0>(trolls[i]) == get<0>(myPos) && get<1>(trolls[i])-1 == get<1>(myPos)) get<1>(trolls[i])--;
        else if (get<1>(trolls[i]) < get<1>(myPos) && charMaze[get<0>(trolls[i])][get<1>(trolls[i])+1] == ' ' || get<0>(trolls[i]) == get<0>(myPos) && get<1>(trolls[i])+1 == get<1>(myPos)) get<1>(trolls[i])++;
        else if (get<0>(trolls[i]) < get<0>(myPos) && charMaze[get<0>(trolls[i])+1][get<1>(trolls[i])] == ' ' || get<0>(trolls[i])+1 == get<0>(myPos) && get<1>(trolls[i]) == get<1>(myPos)) get<0>(trolls[i])++;
        else if (get<0>(trolls[i]) > get<0>(myPos) && charMaze[get<0>(trolls[i])-1][get<1>(trolls[i])] == ' ' || get<0>(trolls[i])-1 == get<0>(myPos) && get<1>(trolls[i]) == get<1>(myPos)) get<0>(trolls[i])--;

        charMaze[get<0>(trolls[i])][get<1>(trolls[i])] = 'T';
        if (get<0>(trolls[i]) == get<0>(myPos) && get<1>(trolls[i]) == get<1>(myPos)) lose = true;
    }
}

void printMap() {
    wmove(stdscr, 0, 0);
    for(int i = 0; i < width*2+1; i++) {
        for(int j = 0; j < width*2+1; j++) {
            if (charMaze[j][i] == 'T')
                waddch(stdscr, 'T' | COLOR_PAIR(1));
            else if (charMaze[j][i] == 'X')
                waddch(stdscr, 'X' | COLOR_PAIR(2));
            else
                waddch(stdscr, charMaze[j][i]);
        }
        waddch(stdscr, '\n');
    }
    wrefresh(stdscr);
}

// TODO: Formatting
void menuUpdate() {
    wmove(stdscr, 10, 14);
    switch (size) {
        case 0:
            waddch(stdscr, 'S');
            break;
        case 1:
            waddch(stdscr, 'M');
            break;
        case 2:
            waddch(stdscr, 'L');
            break;
    }


    wmove(stdscr, 12, 14);
    // TODO: Just do int to char conversion?
    switch (numTrolls) {
        case 0:
            waddch(stdscr, '0');
            break;
        case 1:
            waddch(stdscr, '1');
            break;
        case 2:
            waddch(stdscr, '2');
            break;
        case 3:
            waddch(stdscr, '3');
            break;
        case 4:
            waddch(stdscr, '4');
            break;
        case 5:
            waddch(stdscr, '5');
            break;
        case 6:
            waddch(stdscr, '6');
            break;
        case 7:
            waddch(stdscr, '7');
            break;
        case 8:
            waddch(stdscr, '8');
            break;
        case 9:
            waddch(stdscr, '9');
            break;
    }

    // Moves cursor depending on menu selection
    switch (selection) {
        case 0:
            wmove(stdscr, 8, 3);
            break;
        case 1:
            wmove(stdscr, 10, 3);
            break;
        case 2:
            wmove(stdscr, 12, 3);
            break;
        case 3:
            wmove(stdscr, 14, 3);
            break;
    }
}

// TODO: Can i do ^2?
void gameOver() {
    clearScreen();

    // Draws borders of menu
    wmove(stdscr, 0, 0);
    waddch(stdscr, ACS_ULCORNER);
    wmove(stdscr, 20, 0);
    waddch(stdscr, ACS_LLCORNER);
    wmove(stdscr, 0, 20);
    waddch(stdscr, ACS_URCORNER);
    wmove(stdscr, 20, 20);
    waddch(stdscr, ACS_LRCORNER);

    for (int i = 1; i < 20; i++) {
        wmove(stdscr, 0, i);
        waddch(stdscr, ACS_HLINE);
        wmove(stdscr, 20, i);
        waddch(stdscr, ACS_HLINE);
        wmove(stdscr, i, 0);
        waddch(stdscr, ACS_VLINE);
        wmove(stdscr, i, 20);
        waddch(stdscr, ACS_VLINE);
    }

    wmove(stdscr, 5, 5);

    if (win) {
        waddch(stdscr, 'Y' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, 'U' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, 'W' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, 'I' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, 'N' | A_BOLD | COLOR_PAIR(2));
        waddch(stdscr, '!' | A_BOLD | COLOR_PAIR(2));
    } else if (lose) {
        waddch(stdscr, 'Y' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'U' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'L' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'S' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'E' | A_BOLD | COLOR_PAIR(1));
    } else {
        wmove(stdscr, 5, 7);
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
    }

    wmove(stdscr, 10, 4);

    waddch(stdscr, 'E' | A_BOLD);
    waddch(stdscr, 'N' | A_BOLD);
    waddch(stdscr, 'T' | A_BOLD);
    waddch(stdscr, 'E' | A_BOLD);
    waddch(stdscr, 'R' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, '-' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, 'M' | A_BOLD);
    waddch(stdscr, 'E' | A_BOLD);
    waddch(stdscr, 'N' | A_BOLD);
    waddch(stdscr, 'U' | A_BOLD);

    wmove(stdscr, 13, 4);

    waddch(stdscr, 'E' | A_BOLD);
    waddch(stdscr, 'S' | A_BOLD);
    waddch(stdscr, 'C' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, '-' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, ' ' | A_BOLD);
    waddch(stdscr, 'Q' | A_BOLD);
    waddch(stdscr, 'U' | A_BOLD);
    waddch(stdscr, 'I' | A_BOLD);
    waddch(stdscr, 'T' | A_BOLD);

    wrefresh(stdscr);

    while (true) {
        int ch = getch();
        switch (ch) {
            case 27:    // ESC key pressed - Quit
                done = true;
            case 10:    // ENTER key pressed - Go to menu
                // Clear display
                clearScreen();
                // Show menu
                return;
                break;
        }
    }
}

// TODO: Formatting
void menu() {
    win = false;
    lose = false;

    size = 1;
    numTrolls = 5;
    selection = 0;

    // Draws borders of menu
    wmove(stdscr, 0, 0);
    waddch(stdscr, ACS_ULCORNER);
    wmove(stdscr, 20, 0);
    waddch(stdscr, ACS_LLCORNER);
    wmove(stdscr, 0, 20);
    waddch(stdscr, ACS_URCORNER);
    wmove(stdscr, 20, 20);
    waddch(stdscr, ACS_LRCORNER);

    for (int i = 1; i < 20; i++) {
        wmove(stdscr, 0, i);
        waddch(stdscr, ACS_HLINE);
        wmove(stdscr, 20, i);
        waddch(stdscr, ACS_HLINE);
        wmove(stdscr, i, 0);
        waddch(stdscr, ACS_VLINE);
        wmove(stdscr, i, 20);
        waddch(stdscr, ACS_VLINE);
    }

    wmove(stdscr, 5, 5);
    waddch(stdscr, 'T' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, 'R' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, 'L' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, 'L' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
    waddch(stdscr, 'S' | A_BOLD | COLOR_PAIR(1));

    wmove(stdscr, 8, 8);
    waddch(stdscr, 'S');
    waddch(stdscr, 't');
    waddch(stdscr, 'a');
    waddch(stdscr, 'r');
    waddch(stdscr, 't');

    wmove(stdscr, 10, 6);
    waddch(stdscr, 'S');
    waddch(stdscr, 'i');
    waddch(stdscr, 'z');
    waddch(stdscr, 'e');
    waddch(stdscr, ' ');
    waddch(stdscr, ' ');
    waddch(stdscr, ':');
    wmove(stdscr, 10, 14);
    waddch(stdscr, 'M');

    wmove(stdscr, 12, 6);
    waddch(stdscr, 'T');
    waddch(stdscr, 'r');
    waddch(stdscr, 'o');
    waddch(stdscr, 'l');
    waddch(stdscr, 'l');
    waddch(stdscr, 's');
    waddch(stdscr, ':');
    wmove(stdscr, 12, 14);
    waddch(stdscr, '5');

    wmove(stdscr, 14, 8);
    waddch(stdscr, 'L');
    waddch(stdscr, 'e');
    waddch(stdscr, 'a');
    waddch(stdscr, 'v');
    waddch(stdscr, 'e');

    wmove(stdscr, 8, 3);

    while (true) {
        int press = getch();
        switch (press) {
            case 'k':
            case KEY_UP:
                selection--;
                if (selection == -1) selection = 3;
                menuUpdate();
                break;
            case 'j':
            case KEY_DOWN:
                selection = (selection+1) % 4;
                menuUpdate();
                break;
            case 'l':
            case KEY_LEFT:
                if (selection == 1) {
                    size--;
                    if (size == -1) size = 2;
                } else if (selection == 2) {
                    numTrolls--;
                    if (numTrolls == -1) numTrolls = 9;
                }
                menuUpdate();
                break;
            case 'h':
            case KEY_RIGHT:
                if (selection == 1) {
                    size = (size + 1) % 3;
                } else if (selection == 2) {
                    numTrolls = ((numTrolls + 1) % 10);
                }
                menuUpdate();
                break;
            case 10: // Enter key, KEY_ENTER does not work
                if (selection == 0)
                    return;
                else if (selection == 3){
                    done = true;
                    return;
                }
                break;
            case 27: // ESC key - Quit
                done = true;
                return;
        }
    }
}

void mazeCell(int x, int y, int dir) {
    int choice;
    switch (dir) {
        case N:
            maze[x][y] += S;
            break;
        case S:
            maze[x][y] += N;
            break;
        case E:
            maze[x][y] += W;
            break;
        case W:
            maze[x][y] += E;
            break;
        case 0:         // TODO: Necessary?
            break;
    }

    while (emptyAdjacentCells(x, y)) {
        choice = rand() % 4;

        switch (choice) {
            // N
            case 0:
                // If the cell exists and is untouched
                if (y != 0 && maze[x][y-1] == 0) {
                    maze[x][y] += N;
                    mazeCell(x, y-1, N);
                }
                break;
                // S
            case 1:
                if (y != width-1 && maze[x][y+1] == 0) {
                    maze[x][y] += S;
                    mazeCell(x, y+1, S);
                }
                break;
                // E
            case 2:
                if (x != width-1 && maze[x+1][y] == 0) {
                    maze[x][y] += E;
                    mazeCell(x+1, y, E);
                }
                break;
                // W
            case 3:
                if (x != 0 && maze[x-1][y] == 0) {
                    maze[x][y] += W;
                    mazeCell(x-1, y, W);
                }
                break;
        }
    }
}

bool emptyAdjacentCells(int x, int y) {
    bool n, s, e, w;
    n = !(y == 0 || maze[x][y-1] != 0);
    s = !(y == width-1 || maze[x][y+1] != 0);
    e = !(x == width-1 || maze[x+1][y] != 0);
    w = !(x == 0 || maze[x-1][y] != 0);

    return n | s | e | w;
}

void clearScreen() {
    wmove(stdscr, 0, 0);
    for(int i = 0; i < (width*2+1)*(width*2+1); i++) {
        if (i != 0 && i % (width*2+1) == 0)
            waddch(stdscr, '\n');
        waddch(stdscr, ' ');
    }
    wrefresh(stdscr);

}
