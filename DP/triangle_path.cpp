#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int trianglePath(vector<vector<int>> &triangle) {
    int m = triangle.size();

    for (int i=1; i<m; i++) {
        int n = triangle[i].size();

        for (int j=0; j<n; j++) {
            if (j==0) {
                triangle[i][j] += triangle[i-1][j];
            } else if  (j==n-1) {
                triangle[i][j] += triangle[i-1][j-1];
            } else {
                triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
            }
        }
    }

    int ans =INT_MAX;
    for (int num: triangle[m-1]){
        ans = min(ans, num);
    }
    return ans;
}
int main() {
    vector<vector<int>> triangle= {
        {2},
        {1, 3},
        {2, 4, 1},
        {4, 5, 0, 1}
    };
    cout << trianglePath(triangle) << endl;
    return 0;
}