#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int rnum = rand() % 100;
    int i = 0, num;

    cout << "The number is selected." << endl;

    while(i < 3) {
        cout << "Enter your choice: ";
        cin >> num;

        if (rnum == num) {
            cout << "Correct!!" << endl;
            break;
        } else if (num >= rnum - 5 && num <= rnum + 5) {
            cout << "Hot" << endl;
        } else if (num >= rnum - 25 && num <= rnum + 25) {
            cout << "Warm" << endl;
        } else if (num >= rnum - 55 && num <= rnum + 55) {
            cout << "Cold" << endl;
        } else {
            cout << "Super cold" << endl;
        }
        i++;
    }

    if (i == 3) {
        cout << "Oppsies, you were not able to find the answer" << endl;
        cout << "Btw the number was " << rnum << endl;
    }

    return 0;
}