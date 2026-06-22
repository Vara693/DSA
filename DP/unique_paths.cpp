#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void counting(int i, int j, int m, int n, int &ans) {
    if (i>=m || j>=n) return;

    if (i==m-1 && j==n-1) {
        ans+=1;
        return;
    }

    counting(i+1, j, m, n, ans);
    counting(i, j+1, m, n, ans);
}

int uniquePaths(int m, int n) {
    //1. Recurrsion
    // int ans = 0;
    // counting(0, 0, m, n, ans);
    // return ans;

    //2. Tabulation, S.c=O(mn)
    // vector<vector<int>> dp(m, vector<int> (n, 0));

    // for (int i=0; i<m; i++) {
    //     dp[i][0] = 1;
    // }

    // for (int j=1; j<n; j++) {
    //     dp[0][j] = 1;
    // }

    // for (int i=1; i<m; i++) {
    //     for (int j=1; j<n; j++) {
    //         dp[i][j] = dp[i-1][j] + dp[i][j-1];
    //     }
    // }

    // return dp[m-1][n-1];


    //3. Space optimized tabulation
    vector<int> past(n, 1);
    vector<int> curr(n, 0);
    curr[0] = 1;

    for (int i=1; i<m; i++) {
        for (int j=1; j<n; j++) {
            curr[j] = past[j]+curr[j-1];
        }
        past = curr;
    }

    return past[n-1];
}
int main() {
    cout << uniquePaths(3, 3) << endl;
    return 0;
}