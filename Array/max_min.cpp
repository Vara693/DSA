#include <iostream>
#include<vector>
using namespace std;

// Algorithm maxMin(arr, n):
//     Input: arr (array of size n)
//     Output: maxVal, minVal

//     maxVal ← arr[0]
//     minVal ← arr[0]

//     For i ← 1 to n-1:
//         If arr[i] > maximum:
//             maximum ← arr[i]
//         If arr[i] < minimum:
//             minimum ← arr[i]

//     Return (maximum, minimum)


pair<int, int> maxMin(vector<int> &arr) {
    int maximum = arr[0];
    int minimum = arr[0];
    for (int i=1; i<arr.size(); i++) {
        maximum = max(maximum, arr[i]);
        minimum = min(minimum, arr[i]);
    }
    return {maximum, minimum};
}
int main() {
    int n = 0;
    cout << "Enter size of the array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Input array elements: ";
    for (int i=0; i<n; i++) {
        cin >> nums[i];
    }
    
    auto result = maxMin(nums);
    cout << "The maximum number in array is " << result.first << endl;
    cout << "The minimum number in array is " << result.second;
    return 0;
}