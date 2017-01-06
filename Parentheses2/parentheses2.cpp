#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;

int main(int argc, char* argv[]) {
    char* input = argv[1];
    stack<int> s;
    int length, unclosed = 0;
    while (input[length] != '\0') length++;

    for (int i = 0; i < length; i++) {
        if (input[i] == ')') {
            unclosed--;
            s.pop();
        } else if (input[i] == '(') {
            s.push(i);
            unclosed++;
        }
        if (unclosed < 0) { 
            cout << i << '\n';
            return 0;
        }
    }

    if (s.empty()) cout << length << '\n';
    else cout << s.top() << '\n';

    return 0;
}
