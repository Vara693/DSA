#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char op;
    
    cout << "Enter number 1: " << endl;
    cin >> num1;
    cout << "Enter number 2: " << endl;
    cin >> num2;

    cout << "Enter the operation to perform: " << endl;
    cin >> op;

    if (op == '+'){
        cout << num1 + num2 << endl;
    } else if (op == '-'){
        cout << num1 - num2 << endl;
    } else if (op == '*'){
        cout << num1*num2 << endl;
    } else if (op == '/'){
        cout << num1/num2 << endl;
    } else{
        cout << "Invalid input" <<endl;
    }


    return 0;
}