// #include <iostream>
// using namespace std;
// int factorial(int n){
//     if(n < 0){
//         return 0;
//     }
//     if(n == 1 || n == 0){
//         return 1;
//     } else{
//         return n*factorial(n-1);
//     }
// }
// int npr(int n, int r){
//     int num = factorial(n);
//     int den = factorial(n-r);
//     return num/den;
// }
// int main() {
//     cout << npr(6,3) << endl;
//     return 0;
// }



#include <iostream>
using namespace std;

int factorial(int n){
    if(n < 0){
        return 0;
    }
    if(n == 1 || n == 0){
        return 1;
    } else{
        return n*factorial(n-1);
    }
}

int ncr(int n, int r){
    if(n<r){
        return 0;
    }else{
        int num = factorial(n);
        int den = factorial(n-r);
        return num/(den*factorial(r));
    }
}
int main() {
    cout << ncr(2,4) << endl;
    return 0;
}