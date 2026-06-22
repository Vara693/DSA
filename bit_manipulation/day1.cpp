//Counting the minimum set bit flips to convert start into goal

#include <iostream>
#include <cmath>
using namespace std;

int count_bits (int start, int goal) {
    int res = start^goal;
    int count = 0;

    // for (int i = 0; i < log2(start^goal); i++) {
    //     if ((res & (1 << i)) != 0) count++;
    // }

    while (res) {
        count += res&1;
        res >>= 1;
    }

    return count;
}
int main() {
    cout << count_bits(10, 7);
    return 0;
}