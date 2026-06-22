#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void helper(int idx, vector<vector<int>> &ans, vector<int> &currSet, vector<int> &nums, int target) {
    if (target == 0) {
        ans.push_back(currSet);
        return;
    }

    if (idx>=nums.size()) {
        return;
    }

    if (target<0) return;

    currSet.push_back(nums[idx]);
    helper(idx, ans, currSet, nums, target-nums[idx]);

    currSet.pop_back();
    helper(idx+1, ans, currSet, nums, target);
}
vector<vector<int>> subsetsWithSum(vector<int> &nums, int target) {
    vector<vector<int>> ans;
    vector<int> currSet;
    helper(0, ans, currSet, nums, target);
    return ans;
}
int main() {
    vector<int> nums = {1, 4, 3, 5, 2};
    vector<vector<int>> ans = subsetsWithSum(nums, 6);
    for (auto &it: ans) {
        for (auto &val: it) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}