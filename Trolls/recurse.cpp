#include <iostream>

int maze[10][10];
    const int N = 1;
    const int S = 2;
    const int E = 4;
    const int W = 8;

void mazeCell(int x, int y, int dir);

bool emptyAdjacentCells(int x, int y);

int main() {

    srand (time(NULL));

    char charmaze[21][21];

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            maze[i][j] = 0;

    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 21; j++) {
            charmaze[j][i] = '#';
            if (i%2 == 1 && j%2 == 1)
            charmaze[j][i] = ' ';
        }

    mazeCell(0, 0, 0);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << maze[i][j];
            if (maze[j][i] & 4 == 4)
                charmaze[2*j+2][2*i+1] = ' '; 
            if (maze[j][i] & 2 == 2)
                charmaze[2*j+1][2*i+2] = ' '; 
        }
        std::cout << '\n';
    }

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++)
            std::cout << charmaze[j][i];
        std::cout << '\n';
    }

    /*
       else if (j%2 == 1 && (maze[i/2][j/2] == 4 || maze[i/2][j/2] == 5 || maze[i/2][j/2] == 6 || maze[i/2][j/2] == 7 || maze[i/2][j/2] == 12 || maze[i/2][j/2] == 11)) std::cout << ' ';
       else if (maze[i/2][j/2] == 2 || maze[i/2][j/2] == 3 || maze[i/2][j/2] == 6 || maze[i/2][j/2] == 10 || maze[i/2][j/2] == 11|| maze[i/2][j/2] == 11) std::cout << ' ';
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (j == 0 || j == 20 || i == 0 || i == 20) std::cout << '#';
            else if (i%2 == 1 && j%2 == 1) std::cout << ' ';
            else if (i%2 == 0 && j%2 == 0) std::cout << '#';
               else if (i%2 == 1 && maze[j/2][i/2] & 4 == 4) std::cout << ' ';
               else if (i%2 == 0 && j%2 == 1 && maze[j/2][i/2] & 2 == 2) std::cout << ' ';
            else std::cout << '#';
        }
        std::cout << '\n';
    }
        */

    return 0;
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
        case 0:
            break;
    }

    while (emptyAdjacentCells(x, y)) {
        //std::cout << x, ' ', y;
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
                if (y != 9 && maze[x][y+1] == 0) {
                    maze[x][y] += S;
                    mazeCell(x, y+1, S);
                }
                break;
                // E
            case 2:
                if (x != 9 && maze[x+1][y] == 0) {
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
    std::cout << "AdjacentCells called\n";
    std::cout << (y == 0 || maze[x][y-1] != 0);
    bool n;
    bool s;
    bool e;
    bool w;
    n = !(y == 0 || maze[x][y-1] != 0);
    s = !(y == 9 || maze[x][y+1] != 0);
    e = !(x == 9 || maze[x+1][y] != 0);
    w = !(x == 0 || maze[x-1][y] != 0);

    //std::cout << n, ' ', s, ' ', e, ' ', w, '\n';
    return n | s | e | w;
}
