#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> jump(9, vector<int>(9, -1));

void dfs(int curr, vector<bool>& vis, int length, int &count) {
    if (length >= 4) count++;

    if (length == 9) return;

    for (int next = 0; next < 9; next++) {
        if (vis[next]) continue;

        int mid = jump[curr][next];

        // If jump required and middle not visited → skip
        if (mid != -1 && !vis[mid]) continue;

        vis[next] = true;
        dfs(next, vis, length + 1, count);
        vis[next] = false; // backtrack
    }
}

int main() {
    // Initialize jump matrix
    jump[0][2] = jump[2][0] = 1;
    jump[0][6] = jump[6][0] = 3;
    jump[2][8] = jump[8][2] = 5;
    jump[6][8] = jump[8][6] = 7;
    jump[0][8] = jump[8][0] = 4;
    jump[2][6] = jump[6][2] = 4;
    jump[1][7] = jump[7][1] = 4;
    jump[3][5] = jump[5][3] = 4;

    int count = 0;

    for (int i = 0; i < 9; i++) {
        vector<bool> vis(9, false);
        vis[i] = true;
        dfs(i, vis, 1, count);
    }

    cout << count << endl;  // should print 389112

    return 0;
}