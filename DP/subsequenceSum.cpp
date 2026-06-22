#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool subsequenceSum(vector<int> &nums, int idx, int target) {
    if (target == 0) {
        return true;
    }

    if (idx== nums.size()-1) {
        return nums[idx] == target;
    }

    bool notTake = subsequenceSum(nums, idx+1, target);
    bool take = false;
    if (target>= nums[idx]) {
        take = subsequenceSum(nums, idx+1, target-nums[idx]);
    }

    return take | notTake;
}

bool subsequenceSumMemo(vector<int> &nums, vector<vector<int>> &dp, int idx, int target) {
    if (target == 0) {
        return true;
    }

    if (idx== nums.size()-1) {
        return nums[idx] == target;
    }

    if (dp[idx][target] != -1) {
        return dp[idx][target];
    }

    bool notTake = subsequenceSumMemo(nums, dp, idx+1, target);
    bool take = false;
    if (target>= nums[idx]) {
        take = subsequenceSumMemo(nums, dp, idx+1, target-nums[idx]);
    }

    return dp[idx][target] = take | notTake;
}


bool subsequenceSumTabu(vector<int> &nums, int target) {
    vector<vector<bool>> dp(nums.size(), vector<bool> (target+1, false));
    //base case
    for (int i=0; i<nums.size(); i++) {
        dp[i][0] = true;
    }

    dp[0][nums[0]] = true;

    //nested loops
    for (int i=1; i<nums.size(); i++) {
        for (int j=1; j<=target; j++) {
            bool notTake = dp[i-1][j];
            bool take = false;
            if (j>=nums[i]) {
                take = dp[i-1][j-nums[i]];
            }

            dp[i][j] = take | notTake;
        }
    }

    return dp[nums.size()-1][target];
}

int main() {
    vector<int> nums = {1, 2, 5, 5};
    int target = 4;
    cout << subsequenceSum(nums, 0, target) << endl;

    vector<vector<int>> dp(nums.size(), vector<int> (target+1, -1));
    for (int i=0; i<nums.size(); i++) {
        dp[i][0] = nums[i];
    }
    cout << subsequenceSumMemo(nums, dp, 0, target) << endl;
    cout << subsequenceSumTabu(nums, target) << endl;
    return 0;
}