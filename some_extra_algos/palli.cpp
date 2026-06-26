#include <iostream>
using namespace std;

int ispalli(int n){
    int digit = 0;
    while (n>0){
        digit = n%10 + digit*10;
        n = n/10;
    }
    return digit;
}
int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    if(ispalli(num) == num){
        cout << endl << "Pallindrome" << endl;
    } else {
        cout << "No";
    }

    return 0;
}