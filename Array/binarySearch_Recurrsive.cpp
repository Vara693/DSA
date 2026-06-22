#include <iostream>
#include <vector>
using namespace std;

// Algorithm BinarySearchRecursive(arr, st, end, target):
//     Input: arr (sorted array), st, end (search bounds), target
//     Output: index of target if found, else -1

//     if st > end:
//         return -1

//     mid ← st + (end - st) / 2

//     if arr[mid] == target:
//         return mid
//     else if arr[mid] < target:
//         return BinarySearchRecursive(arr, mid + 1, end, target)
//     else:
//         return BinarySearchRecursive(arr, st, mid - 1, target)

int binarySearch(vector<int> &arr, int st, int end, int target) {
    if (st<=end) {
        int mid = st+ (end-st)/2;
        
        if (arr[mid]<target) {
            return binarySearch(arr, mid+1, end, target);
        } else if (arr[mid]>target){
            return binarySearch(arr, st, mid-1, target);
        } else {
            return mid;
        }
    }
    return -1;
}

// Algorithm BinarySearch(arr, target):
//     Input: arr (sorted array), target (value to search)
//     Output: index of target if found, else -1

//     st ← 0
//     end ← length(arr) - 1

//     while st ≤ end:
//         mid ← st + (end - st) / 2

//         if arr[mid] == target:
//             return mid
//         else if arr[mid] < target:
//             st ← mid + 1
//         else:
//             end ← mid - 1

//     return -1

int binarySearchIterstive(vector<int> &arr, int target) {
    int st = 0;
    int end = arr.size();
    while (st<=end) {
        int mid = st+(end-st)/2;
        if (arr[mid]==target) {
            return mid;
        } else if (arr[mid]<target) {
            st = mid+1;
        } else {
            end = mid-1;
        }
    }
    return -1;
}
int main() {
    int n = 0;
    cout << "Enter size of the array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Input array elements in sorted order: ";
    for (int i=0; i<n; i++) {
        cin >> nums[i];
    }
    cout << endl;
    // sort(nums.begin(), nums.end());
    int target;
    cout << "Enter element to search: ";
    cin >> target;
    cout << endl;
    cout << "Result through recurrsive: " << binarySearch(nums, 0, nums.size()-1, target) << endl;
    cout << "Result through iterative: " << binarySearchIterstive(nums, target) << endl;
    return 0;
}