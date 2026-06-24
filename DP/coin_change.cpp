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

int helperTabu(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end());
    int n = coins.size();
    int count = 0;
    for (int i=n-1; i>=0; i--) {
        while (amount-coins[i] >= 0) {
            amount -= coins[i];
            count++;
        }

        if (amount == 0) break;
    }

    return amount == 0? count: -1;
}

int func(vector<int> &coins, int idx, int amount) {
    if (idx == 0) {
        if (amount % coins[0] == 0) {
            return amount/coins[0];
        }
        else {
            return INT_MAX;
        }
    }

    int notTake = func(coins, idx-1, amount);
    int take = INT_MAX;
    if (coins[idx] <= amount) {
        take = 1+func(coins, idx, amount-coins[idx]);
    }

    return min(take, notTake);
}

int funcMemo(vector<int> &coins, vector<vector<int>> &dp, int idx, int amount) {
    if (idx == 0) {
        if (amount % coins[0] == 0) {
            return amount/coins[0];
        }
        else {
            return INT_MAX;
        }
    }

    if (dp[idx][amount] != -1) return dp[idx][amount];

    int notTake = funcMemo(coins, dp, idx-1, amount);
    int take = INT_MAX;
    if (coins[idx] <= amount) {
        take = 1+funcMemo(coins, dp, idx, amount-coins[idx]);
    }

    return dp[idx][amount] = min(take, notTake);
}

int funcTabu(vector<int> &coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int> (amount+1, INT_MAX));

    for (int a = 0; a<=amount; a++) {
        if (a%coins[0] == 0) {
            dp[0][a] = a/coins[0];
        }
    }

    for (int i=1; i<n; i++) {
        for (int j=0; j<=amount; j++) {
            int notTake = dp[i-1][j];
            int take = INT_MAX;
            if (coins[i] <= j && dp[i][j - coins[i]] != INT_MAX) {
                take = 1+dp[i][j-coins[i]];
            }

            dp[i][j] = min(take, notTake);
        }
    }

    return dp[n-1][amount] == INT_MAX? -1 : dp[n-1][amount];
}

int main() {
    vector<int> coins = {1,2,5};
    int  amount = 11;
    int ans = INT_MAX;
    helper(coins, 0, 0, ans, amount);
    cout << ans << endl;
    cout << helperTabu(coins, amount) << endl;
    cout << func(coins, coins.size()-1, amount) << endl;

    vector<vector<int>> dp(coins.size(), vector<int> (amount+1, -1));
    cout << funcMemo(coins, dp, coins.size()-1, amount) << endl;
    cout << funcTabu(coins, amount) << endl;
    return 0;
}