#include <iostream>
using namespace std;
int main() {
    int n = 7;
    for (int i=1; i<=n; i++) {
        for (int k = 0; k < n - i; k++) {
            cout << "  ";
        }
        for (int j=i; j>0; j--) {
            if (i==j || j==1 || i==n) {
                cout << j << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    return 0;
}