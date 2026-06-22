#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void knapsack(int idx, vector<pair<int, int>> &items, int capacity, int currSum, int &ans) {
    if (capacity < 0) return;

    if (idx>=items.size()) {
        ans = max(ans, currSum);
        return;
    }

    currSum+=items[idx].first;
    knapsack(idx+1, items, capacity-items[idx].second, currSum, ans);

    currSum-=items[idx].first;
    knapsack(idx+1, items, capacity, currSum, ans);
}

int knapsackMemoization(int idx, int capacity, vector<pair<int, int>> &items, vector<vector<int>> &dp) {
    if (idx>=items.size() || capacity <= 0) {
        return 0;
    }

    if (dp[idx][capacity]!=-1) {
        return dp[idx][capacity];
    }

    int notTake = knapsackMemoization(idx+1, capacity, items, dp);
    int take = 0;

    if (items[idx].second <= capacity) {
        take = items[idx].first+knapsackMemoization(idx+1, capacity-items[idx].second, items, dp);
    }

    return dp[idx][capacity] = max(take, notTake);
}

int knapsackTabulation(vector<pair<int, int>> &items, int capacity) {
    int n= items.size();
    vector<vector<int>> dp(n, vector<int> (capacity+1, 0));

    for (int i=items[0].second; i<=capacity; i++) {
        dp[0][i] = items[0].first;
    }

    for (int i=1; i<n; i++) {
        for (int w=0; w<=capacity; w++) {
            int notTake = dp[i-1][w];

            int take = 0;
            if (items[i].second <= w) {
                take = items[i].first + dp[i-1][w-items[i].second];
            }

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n-1][capacity];
}
int main() {
    int capacity = 6;
    vector<pair<int, int>> items = {{30, 3}, {40, 2}, {60, 5}};
    vector<vector<int>> dp(items.size(), vector<int> (capacity+1, -1));
    int ans = 0;
    knapsack(0, items, capacity, 0, ans);
    cout << ans << endl;
    cout << knapsackMemoization(0, capacity, items, dp);
    cout << endl;
    cout << knapsackTabulation(items, capacity);
    return 0;
}