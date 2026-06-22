#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(vector<vector<int>> &nums, int capacity) {
    int maxCost = 0;
    int currCost = 0;
    int left = 0, w=0;
    sort(nums.begin(), nums.end(), [] (vector<int> &a, vector<int> &b) {
        return (double)a[0]/a[1] > (double) b[0]/b[1];
    });

    for (auto &num: nums) {
        while (w+num[1] > capacity) {
            w-=nums[left][1];
            currCost -= nums[left][0];
            left++;
        }

        currCost += num[0];
        w+=num[1];
        maxCost = max(maxCost, currCost);
    }

    return maxCost;
}
int main() {
    vector<vector<int>> nums = {{5, 2}, {3, 1}, {10, 4}, {8, 3}};
    cout << knapsack(nums, 6) << endl;
    return 0;
}