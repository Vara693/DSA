#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void swapped(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(int idx, string &s) {
    if (idx>=s.size()) {
        for (char ch: s) {
            cout << ch << " ";
        }

        cout << endl;
        return;
    }

    for (int i=idx; i<s.size(); i++) {
        swapped(&s[idx], &s[i]);
        permutation(idx+1, s);
        swapped(&s[idx], &s[i]);
    }
}
int main() {
    string s = "ABA";
    permutation(0, s);
    return 0;
}