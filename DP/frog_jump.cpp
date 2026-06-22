#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int frogJump(int idx, vector<int> &consumptions) {
    if (idx==0) return 0;

    int left = frogJump(idx-1, consumptions) + abs(consumptions[idx] - consumptions[idx-1]);
    int right = INT_MAX;
    if (idx>1) {
        right = frogJump(idx-2, consumptions) + abs(consumptions[idx] - consumptions[idx-2]);
    }

    return min(left, right);
}

//TC = O(N), SC = O(N) + O(N)
int frogJumpMemoization(int idx, vector<int> &consumptions, vector<int> &dp) {
    // if (idx==0) return 0;
    if (dp[idx] != -1) return dp[idx];

    int left = frogJumpMemoization(idx-1, consumptions, dp) + abs(consumptions[idx] - consumptions[idx-1]);
    int right = INT_MAX;
    if (idx>1) {
        right = frogJumpMemoization(idx-2, consumptions, dp) + abs(consumptions[idx] - consumptions[idx-2]);
    }

    return dp[idx] = min(left, right);
}

//O(N)
int tabulation(vector<int> &consumptions) {
    int n = consumptions.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    dp[1] = abs(consumptions[1] - consumptions[0]);

    for (int i=2; i<n; i++) {
        int left = dp[i-1] + abs(consumptions[i] - consumptions[i-1]);
        int right = dp[i-2] + abs(consumptions[i] - consumptions[i-2]);

        dp[i] = min(left, right);
    }

    return dp[n-1];
}

//TC = O(N), SC = O(N)
int tabulationSpace(vector<int> &consumptions) {
    int n = consumptions.size();
    int prev2 = 0;
    int prev1 = abs(consumptions[1] - consumptions[0]);

    for (int i=2; i<n; i++) {
        int left = prev1 + abs(consumptions[i] - consumptions[i-1]);
        int right = prev2 + abs(consumptions[i] - consumptions[i-2]);

        prev2 = prev1;
        prev1 = min(left, right);
    }

    return prev1;
}

int main() {
    vector<int> consumptions = {30, 10, 60, 10, 60, 50};
    int n = consumptions.size();
    cout << frogJump(n-1, consumptions) << endl;
    vector<int> dp(n, -1);
    dp[0] = 0;
    cout << frogJumpMemoization(n-1, consumptions, dp) << endl;
    cout << tabulation(consumptions) << endl;
    cout << tabulationSpace(consumptions) << endl;
    return 0;
}