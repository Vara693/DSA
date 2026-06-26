// #include <iostream>
// using namespace std;

// int factorial(int n){
//     if(n<0){
//         return 0;
//     }
//     if(n==1 || n==0){
//         return 1;
//     }
//     return n*factorial(n-1);
// }
// int main() {
//     int num;
//     int fac;
//     cout << "Enter number: " << endl;
//     cin >> num;
//     fac = factorial(num);

//     if(fac == 0){
//         cout << "Negative numbers do not have a factorial: " << num << endl;
//     } else {
//         cout << "The factorial of " << num << " is " << fac << endl;
//     }
//     return 0;
// }


#include <iostream>
using namespace std;
bool isprime(int n){
    if(n <= 1){
        return false;
    } else{
        for(int i=2; i<n; i++){
            if(n%i == 0){
                return false;
            }
        }
    } return true;
}
int main() {
    int num;
    cout << "Enter the number: ";
    cin >> num;
    if(isprime(num)){
        cout << num << " is a prime number" << endl;
    } else {
        cout << num << " is not a prime number" << endl;
    }
    return 0;
}


// #include <iostream>
// using namespace std;
// int add_num(int a, int b){
//     return a+b;
// }
// int main() {
//     int a,b;
//     cout << "Enter number 1: ";
//     cin >> a;
//     cout << "Enter number 2: ";
//     cin >> b;
//     cout << "The sum of " << a << " and " << b << " is " << add_num(a,b) << endl;

//     return 0;
// }