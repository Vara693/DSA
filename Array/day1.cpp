#include <iostream>
#include<vector>
using namespace std;

vector<int> pair_sum(vector<int> nums, int target) {
    int left = 0;
    int right = nums.size()-1;
    vector<int> ans;

    while (left<right) {
        int sum = nums[left] + nums[right];

        if (sum < target) {
            left++;
        } else if (sum > target) {
            right--;
        } else {
            ans.push_back(left);
            ans.push_back(right);
            left++;
            right--;
        }
    }

    return ans;
} 

int majority_moore(vector<int> ans) {
    int res = 0, freq = 0;
    for (int val: ans) {
        if (freq == 0) {
            res = val;
        }

        if (res == val) freq++;
        else freq--;
    }

    return res;
}
int main() {
    vector<int> nums = {2,4,5,7,9,10,14,20};
    vector<int> v = {1,2,3,1,2,2,4,2,5,1,5,5,5,5,5};
    int tar = 9;
    vector<int> ans = pair_sum(nums, tar);

    for (int i: ans) {
        cout << i << " ";
    }
    cout << endl;

    cout << majority_moore(v) << endl;
    return 0;
}