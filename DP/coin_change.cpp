#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void helper(vector<int>& coins, int idx, int currCoins, int &ans, int amount) {
    if (amount == 0) {
        ans = min(ans, currCoins);
        return;
    }

    if (amount<0 || idx>= coins.size()) return;

    amount -= coins[idx];
    helper(coins, idx, currCoins+1, ans, amount);

    amount += coins[idx];
    helper(coins, idx+1, currCoins, ans, amount);
}

int helperTabu(vector<int>& nums, int amount) {
    int n = nums.size();
    int coins = 0;
    for (int i=n-1; i>=0; i--) {
        while (amount-nums[i] >= 0) {
            amount -= nums[i];
            coins++;
        }

        if (amount == 0) break;
    }

    return amount == 0? coins: -1;
}
int main() {
    vector<int> coins = {1,2,5};
    int  amount = 11;
    int ans = INT_MAX;
    helper(coins, 0, 0, ans, amount);
    cout << ans << endl;
    cout << helperTabu(coins, amount) << endl;
    return 0;
}