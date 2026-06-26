// #include <iostream>
// using namespace std;
// int all_factors(int n){
//     for(int i = 1; i <=n; i++){
//         if(n%i == 0){
//             cout << i << " ";
//         }
//     }
// }
// int is_prime(int n){
//     if()
//     for(int j = 2; j < n; j++){
//         if(n%j == 0){
//             return 0;
//         }
//     }
//     return 1;
// }
// int main() {
//     all_factors(20);
//     return 0;
// }



//prime_factors
#include <iostream>
using namespace std;

int is_prime(int n){
    for(int j = 2; j < n; j++){
        if(n%j == 0){
            return 0;
        }
    }
    return 1;
}

int prime_factors(int n){
    for(int i = 2; i <= n; i++){
        if(n%i == 0 && is_prime(i) == 1){
            cout << i << " ";
        }
    }
}

int main() {
    prime_factors(60);
    return 0;
}