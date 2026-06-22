#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void counting(vector<vector<int>>& obstacleGrid, int &ans, int i, int j, int m, int n) {
    if (i==m-1 && j==n-1) {
        ans++;
        return ;
    }

    if (i>=m || j>=n) return;

    if (obstacleGrid[i][j] == 1) {
        return;
    }

    counting(obstacleGrid, ans, i+1, j, m, n);
    counting(obstacleGrid, ans, i, j+1, m, n);
}

int uniquePathsTwo(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid[0].size();
    int m = obstacleGrid.size();

    vector<int> past(n, 1);
    vector<int> curr(n, 0);
    curr[0] = 1;

    for (int i=1; i<m; i++) {
        for (int j=1; j<n; j++) {
            if (obstacleGrid[i][j] == 1) continue;

            curr[j] = curr[j-1] + past[j];
        }

        past = curr;
    }

    return past[n-1];
}
int main() {
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    int ans = 0;
    int n = obstacleGrid[0].size();
    int m = obstacleGrid.size();

    counting(obstacleGrid, ans, 0, 0, m, n);
    cout << ans << endl;
    cout << uniquePathsTwo(obstacleGrid) << endl;
    return 0;
}