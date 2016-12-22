#include <iostream>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

using namespace std;

// End of game flag
bool win = false;
bool lose = false;

int width;

// Character positions
int charPos;
int numTrolls = 5;
int size = 1;

// Menu navigation
int selection = 0;

string map;

// Picks a map based on the requested size
// TODO: Generate a map rather than choosing from 3 pre-selected ones
void mapGen();

// Causes every troll to move towards the player
// TODO: Let the trolls move randomly when not near the player
void trollMove(int trolls[]);

// Updates the display of the game
void printMap();

// Allows menu navigation before the game starts
void menuUpdate();

// Displays the result of the game
void gameOver();

int main() {
    // Window Creation //
    initscr();
    noecho();

    srand (time(NULL));

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    bool startGame = false;


    keypad(stdscr, TRUE);

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

    do {
        int press = getch();
        switch (press) {
            case KEY_UP:
                selection--;
                if (selection == -1) selection = 3;
                menuUpdate();
                break;
            case KEY_DOWN:
                selection = (selection+1) % 4;
                menuUpdate();
                break;
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
                    startGame = true;
                else if (selection == 3){
                    endwin();
                    return 0;
                }
                break;
        }
    } while (!startGame);

    mapGen();

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

    gameOver();

    endwin();
    return 0;
}

void mapGen() {
    switch (size) {
        case 0:
            width = 37;
            map =
                "#####################################"
                "# #       #       #     #         # #"
                "# # ##### # ### ##### ### ### ### # #"
                "#       #   # #     #     # # #   # #"
                "##### # ##### ##### ### # # # ##### #"
                "#   # #       #     # # # # #     # #"
                "# # ####### # # ##### ### # ##### # #"
                "# #       # # #   #     #     #   # #"
                "# ####### ### ### # ### ##### # ### #"
                "#     #   # #   # #   #     # #     #"
                "# ### ### # ### # ##### # # # #######"
                "#   #   # # #   #   #   # # #   #   #"
                "####### # # # ##### # ### # ### ### #"
                "#     # #     #   # #   # #   #     #"
                "# ### # ##### ### # ### ### ####### #"
                "# #   #     #     #   # # #       # #"
                "# # ##### # ### ##### # # ####### # #"
                "# #     # # # # #     #       # #   #"
                "# ##### # # # ### ##### ##### # #####"
                "# #   # # #     #     # #   #       #"
                "# # ### ### ### ##### ### # ##### # #"
                "# #         #     #       #       # #"
                "#X###################################";
            break;
        case 1:
            width = 73;
            map = 
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
            break;
        case 2:
            width = 64;
            map =
                "################################################################"
                "#        #        #                                            #"
                "#  ####  #  #######  ############################  ##########  #"
                "#     #     #        #     #     #              #     #        #"
                "####  #  ####  #######  #  #  #  #  ##########  ####  #  #######"
                "#     #  #     #        #     #  #        #  #  #     #     #  #"
                "#  ####  #  ####  ###################  #######  ##########  ####"
                "#  #     #  #  #  #              #  #  #     #        #  #     #"
                "#  #######  ####  #  ##########  #  #  #  #  ####  #  #######  #"
                "#        #  #     #     #     #  #  #     #     #  #           #"
                "#  ####  #  #  #######  ####  #  #############  #  #############"
                "#  #     #  #        #     #  #              #  #           #  #"
                "#  #  ####  #############  #  #############  #  ####  ####  ####"
                "#  #  #                    #              #  #     #  #  #     #"
                "#  #  #  ######################  #######  ## ####  #  #  ####  #"
                "#  #        #     #                    #  #     #  #     #     #"
                "#  #######  #  #  #  ####  #######  #######  #  #  ####  #  ####"
                "#  #        #  #  #     #        #  #        #  #  #  #  #     #"
                "#  #  #######  #  ####  #  ##########  ##########  #  #  ####  #"
                "#  #  #        #     #  #     #     #           #  #     #  #  #"
                "#  #  #  #############  ####  #  #############  #  ##########  #"
                "#  #                       #  #     #  #  #     #        #  #  #"
                "#  #  ############################  #######  ##########  ####  #"
                "#  #        #     #  #        #  #  #  #              #  #     #"
                "##########  #  #  #  #  ####  ####  ####  ####  #######  #  ####"
                "#     #     #  #  #  #  #  #        #  #  #     #     #  #     #"
                "#  ####  ####  #  #  #  ################  #  ####  #  #  #######"
                "#           #  #  #  #                 #  #  #     #  #        #"
                "##########  ####  #  ################  #  #  ################  #"
                "#                 #                 #     #              #     X"
                "################################################################";
            break;
    }
}

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

void gameOver() {
    wmove(stdscr, 0, 0);
    for(int i = 0; i < map.length(); i++) {
        if (i != 0 && i % width == 0)
            waddch(stdscr, '\n');
        waddch(stdscr, ' ');
    }


    wmove(stdscr, 10, width/2-4);

    if (win && !lose) {
        waddch(stdscr, 'Y' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'U' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'W' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'I' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'N' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '!' | A_BOLD | COLOR_PAIR(1));
    } else if (!win && lose) {
        waddch(stdscr, 'Y' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'U' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, ' ' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'L' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'O' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'S' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, 'E' | A_BOLD | COLOR_PAIR(1));
    } else {
        wmove(stdscr, 10, width/2-2);
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
        waddch(stdscr, '?' | A_BOLD | COLOR_PAIR(1));
    }

    wrefresh(stdscr);
    int ch = getch();
    if (ch)
        return;
}
