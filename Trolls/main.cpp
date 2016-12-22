#include <iostream>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

using namespace std;

// End of game flag
bool win = false;
bool lose = false;

int width = 73;
int height = 23;

// Character positions
int charPos;
int numTrolls = 5;

// 73 by 23
string map = 
"#########################################################################"
"#   #               #               #           #                   #   #"
"#   #   #########   #   #####   #########   #####   #####   #####   #   #"
"#               #       #   #           #           #   #   #       #   #"
"#########   #   #########   #########   #####   #   #   #   #########   #"
"#       #   #               #           #   #   #   #   #           #   #"
"#   #   #############   #   #   #########   #####   #   #########   #   #"
"#   #               #   #   #       #           #           #       #   #"
"#   #############   #####   #####   #   #####   #########   #   #####   #"
"#           #       #   #       #   #       #           #   #           #"
"#   #####   #####   #   #####   #   #########   #   #   #   #############"
"#       #       #   #   #       #       #       #   #   #       #       #"
"#############   #   #   #   #########   #   #####   #   #####   #####   #"
"#           #   #           #       #   #       #   #       #           #"
"#   #####   #   #########   #####   #   #####   #####   #############   #"
"#   #       #           #           #       #   #   #               #   #"
"#   #   #########   #   #####   #########   #   #   #############   #   #"
"#   #           #   #   #   #   #           #               #   #       #"
"#   #########   #   #   #   #####   #########   #########   #   #########"
"#   #       #   #   #           #           #   #       #               #"
"#   #   #####   #####   #####   #########   #####   #   #########   #   #"
"#   #                   #           #               #               #   #"
"# X #####################################################################";

void trollMove(int trolls[]) {
    for (int i = 0; i < numTrolls; i++) {
        map[trolls[i]] = ' ';

        // Check if troll should move up
        if (trolls[i]/width > charPos/width && map[trolls[i]-width] == ' ' || trolls[i]-width == charPos)
            trolls[i] -= width;
        else if (trolls[i]/width < charPos/width && map[trolls[i]+width] == ' ' || trolls[i]+width == charPos)
            trolls[i] += width;
        else if (trolls[i]%width < charPos%width && map[trolls[i]+1] == ' ' || trolls[i]+1 == charPos)
            trolls[i]++;
        else if (trolls[i]%width > charPos%width && map[trolls[i]-1] == ' ' || trolls[i]-1 == charPos)
            trolls[i]--;

        map[trolls[i]] = 'T';
        if (trolls[i] == charPos) lose = true;
    }

}
void printMap() {
    wmove(stdscr, 0, 0);
    for(int i = 0; i < map.length(); i++) {
        if (i != 0 && i % width == 0)
            waddch(stdscr, '\n');
        if (map[i] == 'T')
            waddch(stdscr, 'T' | COLOR_PAIR(1));
        else if (map[i] == 'X')
            waddch(stdscr, 'X' | COLOR_PAIR(2));
        else
            waddch(stdscr, map[i]);
    }
    wrefresh(stdscr);
}

int main() {
    // Window Creation //
    initscr();
    noecho();

    srand (time(NULL));

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    bool game = true;
    bool startGame = false;


    keypad(stdscr, TRUE);

    wmove(stdscr, 5, 5);
    waddch(stdscr, 'T' | COLOR_PAIR(1));
    waddch(stdscr, ' ' | COLOR_PAIR(1));
    waddch(stdscr, 'R' | COLOR_PAIR(1));
    waddch(stdscr, ' ' | COLOR_PAIR(1));
    waddch(stdscr, 'O' | COLOR_PAIR(1));
    waddch(stdscr, ' ' | COLOR_PAIR(1));
    waddch(stdscr, 'L' | COLOR_PAIR(1));
    waddch(stdscr, ' ' | COLOR_PAIR(1));
    waddch(stdscr, 'L' | COLOR_PAIR(1));
    waddch(stdscr, ' ' | COLOR_PAIR(1));
    waddch(stdscr, 'S' | COLOR_PAIR(1));

    wmove(stdscr, 10, 8);
    waddch(stdscr, 'S');
    waddch(stdscr, 't');
    waddch(stdscr, 'a');
    waddch(stdscr, 'r');
    waddch(stdscr, 't');

    wmove(stdscr, 13, 8);
    waddch(stdscr, 'L');
    waddch(stdscr, 'e');
    waddch(stdscr, 'a');
    waddch(stdscr, 'v');
    waddch(stdscr, 'e');

    wmove(stdscr, 10, 5);

    do {
        int press = getch();
        switch (press) {
            case KEY_UP:
            case KEY_DOWN:
                if (game)
                    wmove(stdscr, 13, 5);
                else
                    wmove(stdscr, 10, 5);
                game = !game;
                break;
            case 10:    // Enter key, KEY_ENTER does not work
                if (game)
                    startGame = true;
                else {
                    endwin();
                    return 0;
                }
                break;
        }
    } while (!startGame);

    int trolls[numTrolls];

    // Character Placement //
    do { charPos = rand() % map.length(); } while (map[charPos] != ' ');
    map[charPos] = '^';

    for (int i = 0; i < numTrolls; i++) {
        do { trolls[i] = rand() % map.length(); } while (map[trolls[i]] != ' ' );
        map[trolls[i]] = 'T';
    }


    printMap();
    wmove(stdscr, charPos / width, charPos % width);

    while(!win && !lose) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                map[charPos] = ' ';
                if (map[charPos-width] == 'X')
                    win = true;
                else if (map[charPos-width] == '#' && map[charPos-2*width] == ' ') {
                    map[charPos-width] = ' ';
                    map[charPos-2*width] = '#';
                } 
                if (map[charPos-width] == ' ') {
                    charPos -= width;
                }
                map[charPos] = '^';
                break;
            case KEY_DOWN:
                map[charPos] = ' ';
                if (map[charPos+width] == 'X')
                    win = true;
                else if (map[charPos+width] == '#' && map[charPos+2*width] == ' ') {
                    map[charPos+width] = ' ';
                    map[charPos+2*width] = '#';
                } 
                if (map[charPos+width] == ' ') {
                    charPos += width;
                }
                map[charPos] = 'v';
                break;
            case KEY_LEFT:
                map[charPos] = ' ';
                if (map[charPos-1] == 'X')
                    win = true;
                else if (map[charPos-1] == '#' && map[charPos-2] == ' ') {
                    map[charPos-1] = ' ';
                    map[charPos-2] = '#';
                } 
                if (map[charPos-1] == ' ') {
                    charPos--;
                }
                map[charPos] = '<';
                break;
            case KEY_RIGHT:
                map[charPos] = ' ';
                if (map[charPos+1] == 'X')
                    win = true;
                else if (map[charPos+1] == '#' && map[charPos+2] == ' ') {
                    map[charPos+1] = ' ';
                    map[charPos+2] = '#';
                } 
                if (map[charPos+1] == ' ') {
                    charPos++;
                }
                map[charPos] = '>';
                break;
        }

        trollMove(trolls);
        printMap();
        wmove(stdscr, (charPos/width), (charPos % width));
    }

    endwin();

    // TODO: I get a '%' after the output? \n does not fix it
    if (win) cout << "You Won!";
    else if (lose) cout << "You frikkin moron, you just lost!";
    else cout << "The game is over for some reason!";

    return 0;
}

