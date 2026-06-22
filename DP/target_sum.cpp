#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void targetSum(vector<int> &nums, int idx, int &count, int ans, int target) {
    // if (target == ans) {
    //     count++;
    //     return;
    // }

    if (idx==nums.size()) {
        if (ans == target) count++;
        return;
    }

    targetSum(nums, idx+1, count, ans+nums[idx], target);
    targetSum(nums, idx+1, count, ans-nums[idx], target);
}

// int findTargetSumWays(vector<int>& nums, int target) {
//     vector<int> nums = {1,1,1,1,1};
//     int target = 3;
//     int count = 0;

//     targetSum(nums, 0, count, 0, target);
//     cout << count << endl;
// }

int main() {
    vector<int> nums = {1,1,1,1,1};
    int target = 3;
    int count = 0;

    targetSum(nums, 0, count, 0, target);
    cout << count << endl;
    return 0;
}