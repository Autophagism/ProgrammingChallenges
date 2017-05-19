#include <stdio.h>

char key[15][15];

// Runs the character through the key to get the decrypted character
char decryptLetter(char letter){
    int xpos, ypos;  // X or Y value the letter starts at
    int xvel = 0, yvel = 0;    // Side the letter is on (direction it travels)

    // Checks full key for match
    // Could check only perimeter; would be faster but take more code
    // Fast either way, not worth the trouble
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
            if (key[x][y] == letter) {
                xpos = x;
                ypos = y;
            }

    if ((int)letter >= 'A' && (int)letter <= 'M') xvel = 1;
    else if ((int)letter >= 'N' && (int)letter <= 'Z') yvel = -1;
    else if ((int)letter >= 'a' && (int)letter <= 'm') yvel = 1;
    else if ((int)letter >= 'n' && (int)letter <= 'z') xvel = -1;
    else return '?';    // Character should be a letter of the alphabet!

    do {
        xpos += xvel;
        ypos += yvel;

        if (key[xpos][ypos] == '\\') {
            if (xvel) {
                yvel = xvel;
                xvel = 0;
            } else {
                xvel = yvel;
                yvel = 0;
            }
        } else if (key[xpos][ypos] == '/') {
            if (xvel) {
                yvel -= xvel;
                xvel = 0;
            } else {
                xvel -= yvel;
                yvel = 0;
            }
        }
    } while(xpos != 0 && xpos != 14 && ypos != 0 && ypos != 14);

    return key[xpos][ypos];
}

// Adds a border of letters to the key
void keyBorder() {
    for(int i = 0; i < 13; i++) {
        key[0][i+1] = 'A'+i;
        key[i+1][14] = 'N'+i;
        key[i+1][0] = 'a'+i;
        key[14][i+1] = 'n'+i;
    }
}

int main(int arg, char* argv[]) {
    keyBorder();
    char* givenKey = argv[1];
    char* encrypted = argv[2];

    for (int y = 0; y < 13; y++) {
        for (int x = 0; x < 13; x++) {
            // y is multiplied by 14 rather than 13 to ignore '\n'
            key[x+1][y+1] = givenKey[x+14*y];
        }
    }

    for(int x = 0; encrypted[x] != '\0'; x++) {
        printf("%c", decryptLetter(encrypted[x]));
    }

    printf("\n");

    return 0;
}
