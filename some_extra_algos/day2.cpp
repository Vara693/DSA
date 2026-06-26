// //Given n, count all 'a' and 'b' that satisfy the condition a^3 + b^3 = n. Where (a, b) and (b, a) are considered two different pairs
// #include <iostream>
// #include <cmath>
// using namespace std;

// int main() {
//     int num, i;
//     int count = 0;
//     cout << "Enter a number: "<< endl;
//     cin>>num;
//     for(i = 1; i <= num; i++){
//         for(int j = 0; j <= num; j++){
//             if(pow(i,3) + pow(j,3) == num){
//                 count++;
//                 cout << "(" << i << "," << j << ")" << endl;
                           
//             }
//         }
//     }

//     cout << count << endl;
//     return 0;
// }

#include <iostream>
using namespace std;
int hcf(int a,int b){
    int out;
    if(a<b){
        out = a;
    } else if(b>a){
        out = b;
    } 
    while(out != 0){
        if(a%out ==0 && b%out ==0){
            break;
        }
        out--;
    }
    return out;
}
int main() {
    int num1,num2;
    cout << "Enter number 1: " << endl;
    cin >> num1;
    cout << "Enter number 2: " << endl;
    cin >> num2;
    cout << "The hcf of " << num1 << " and " << num2 << " is " << hcf(num1,num2) << endl;
    return 0;
}


