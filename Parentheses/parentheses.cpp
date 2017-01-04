#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;

int main(int argc, char* argv[]) {
    stack<int> s;
    int length = 0;
    while (argv[1][length] != '\0') length++;
    bool successive[length];

    for (int i = 0; i < length; i++) {
        successive[i] = false;
        if (argv[1][i] == '(') {
            if(argv[1][i-1] == '(') successive[i] = true;
            s.push(i);
        } else if (argv[1][i] == ')') {
            if(successive[s.top()] && argv[1][i+1] == ')') {
                argv[1][s.top()] = '\0';
                argv[1][i] = '\0';
            }
            successive[s.top()] = false;
            s.pop();
        }
    }

    for (int i = 0; i < length; i++)
        if (argv[1][i] == ')' && argv[1][i-1] == '(') {
            argv[1][i] = '\0';
            argv[1][i-1] = '\0';
        }

    for (int i = 0; i < length; i++) cout << argv[1][i];
    cout << '\n';
        
    return 0;
}
