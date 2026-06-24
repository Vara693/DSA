#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int func(vector<int> &coins, int idx, int amount) {
    if (idx == 0) {
        if (amount == 0) return 1;
        if (amount == coins[0]) return 1;
        return 0;
    }

    if (amount < 0) {
        return 0;
    }

    int notTake = func(coins, idx-1, amount);
    int take = 0;
    if (coins[idx] <= amount) {
        take = func(coins, idx-1, amount-coins[idx]);
    }

    return take + notTake;
}

int main() {
    vector<int> nums = {1, 2, 3};
    int amount = 3;
    cout << func(nums, nums.size()-1, amount) << endl;
    return 0;
}