#include <iostream>
#include <vector>
using namespace std;

int BinarySearch(int st, int end, int tar, vector<int> &arr) {
    if (st <= end) {
        int mid = st + (end - st)/2;

        if (arr[mid] == tar) {
            return mid;
        } else if (tar > arr[mid]) {
            return BinarySearch(mid+1, end, tar, arr);
        } else {
            return BinarySearch(st, mid -1, tar, arr);
        }
    }

    return st;
}
int main() {
    vector <int> arr = {10, 20, 30, 40, 50, 51};

    cout << BinarySearch(0, arr.size()-1, 58, arr);
    return 0;
}