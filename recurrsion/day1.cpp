#include <iostream>
#include <vector>
#include <string>
using namespace std;

int dectobin(int n) {
    if (n==0) {
        return 0;
    }

    return n%2 + 10*dectobin(n/2);
}

int sumarray(vector<int> &arr, int i) {
    if(i == arr.size() - 1) {
        return arr[i];
    }
    return arr[i] + sumarray(arr, i+1);
    
}

string revstring(string s, int i){
    string rev = "";
    if (i == s.size() - 1) {
        return rev + s[i];
    }

    return revstring(s, i+1) + s[i];
}

void printSubsets(vector<int> &nums, vector<int> ans, int i) {
    if (i==nums.size()) {
        for (int val: ans) {
            cout << val << " ";
        }
        cout << endl;
        return;
    }

    //Element Accepted
    ans.push_back(nums[i]);
    printSubsets(nums, ans, i+1);

    //Element Rejected
    ans.pop_back();
    printSubsets(nums, ans, i+1);
}

int main() {
    vector <int> arr = {1,2,3,4,5};
    string s = "Varadraj";
    cout << dectobin(10) << endl;
    cout << sumarray(arr, 0) << endl;
    cout << revstring(s, 0) << endl;

    vector<int> nums = {1,2,3};
    vector<int> ans;
    printSubsets(nums, ans, 0);
    return 0;
}