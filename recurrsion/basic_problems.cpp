#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

//1 to n using backtracking
void printOneToN(int n) {
    if (n==0) return;
    printOneToN(n-1);
    cout << n << endl;
}

//n to 1 using backtracking
void printNToOne(int cnt, int n) {
    if (cnt > n) return;
    printNToOne(cnt+1, n);
    cout << cnt << endl;
}


//pallindrome
bool pallindrome(string s, int l) {
    if (l>=s.size()/2) return true;

    if (s[l] != s[s.size()-l-1]) return false;

    return pallindrome(s, l+1);
} 

//subsequences
void subSequence(vector<int> &subs, vector<int> &nums, int idx, int n, int target) {
    if (target < 0) {
        return;
    }
    if (idx>=n) {
        if (target == 0) {
            for (int i: subs) {
                cout << i;
            }
            cout << endl;
        }
        return;
    }

    subs.push_back(nums[idx]);
    subSequence(subs, nums, idx+1, n, target-nums[idx]);

    subs.pop_back();
    subSequence(subs, nums, idx+1, n, target);
}
int main() {
    printOneToN(5);
    printNToOne(1, 5);

    pallindrome("MAD", 0)? cout << "true": cout << "false";
    cout << endl;

    vector<int> nums = {3, 1, 2};
    vector<int> subs;
    subSequence(subs, nums, 0, nums.size(), 3);
    return 0;
}