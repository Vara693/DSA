#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

//Recurrsive approach: O(2**n)
int lengthOfLongestSubsequenceR(vector<int>& nums, int idx, int target) {
    if (idx == 0) {
        if  (target == 0) {
            return 0;
        }

        if (target == nums[idx]) {
            return 1;
        }

        return -1e9;
    }


    int notTake = lengthOfLongestSubsequenceR(nums, idx-1, target);
    int take = -1e9;
    if (nums[idx] <= target) {
        take = 1+lengthOfLongestSubsequenceR(nums, idx-1, target-nums[idx]);
    }

    return max(take, notTake);
}

//Memoization: O(n*target)
int lengthOfLongestSubsequenceMemo(vector<int>& nums, vector<vector<int>> &dp, int idx, int target) {
    if (idx == 0) {
        if  (target == 0) {
            return 0;
        }

        if (target == nums[idx]) {
            return 1;
        }

        return -1e9;
    }

    if (dp[idx][target] != -1) return dp[idx][target];

    int notTake = lengthOfLongestSubsequenceMemo(nums, dp, idx-1, target);
    int take = -1e9;
    if (nums[idx] <= target) {
        take = 1+lengthOfLongestSubsequenceMemo(nums, dp, idx-1, target-nums[idx]);
    }

    return dp[idx][target] = max(take, notTake);
}

//Tabulation: O(n*target)
int lengthOfLongestSubsequenceTabu(vector<int> &nums, int target) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int> (target+1, -1e9));

    dp[0][0] = 0;
    dp[0][nums[0]] = 1;

    for (int i=1; i <n; i++) {
        for (int j=0; j<=target; j++) {
            int notTake = dp[i-1][j];
            int take = -1e9;
            if (nums[i] <= j && dp[i-1][j-nums[i]] != -1e9) {
                take = 1+dp[i-1][j-nums[i]];
            }

            dp[i][j] = max(take, notTake);
        }
    }

    return dp[n-1][target] == -1e9? -1: dp[n-1][target];
}

int main() {
    vector<int> nums = {1,2,3,4,5};
    int n = nums.size();
    int target = 9;

    cout << lengthOfLongestSubsequenceR(nums, n-1, target) << endl;

    vector<vector<int>> dp(n, vector<int> (target+1, -1));
    cout << lengthOfLongestSubsequenceMemo(nums, dp, n-1, target) << endl;
    cout << lengthOfLongestSubsequenceTabu(nums, target) << endl;
    return 0;
}