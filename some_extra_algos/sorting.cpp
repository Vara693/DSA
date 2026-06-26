#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int> &nums) {
    int n = nums.size();
    bool isSort;
    for (int i = 0; i<n; i++) {
        isSort = true;
        for (int j = 0; j<n-i-1; j++) {
            if (nums[j] > nums[j+1]) {
                swap(nums[j], nums[j+1]);
                isSort = false;
            }
        }
        if (isSort) break;
    }
}

void SelectionSort(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i<n-1; i++) {
        int s_index = i;
        for (int j = i; j <n; j++) {
            if (nums[j] < nums[s_index]) {
                s_index = j;
            }
        }
        swap(nums[i], nums[s_index]);
    }
}

void InsertionSort(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i<n; i++) {
        int curr = nums[i];
        int prev = i-1;

        while (prev >=0 && nums[prev] > curr) {
            nums[prev +1] = nums[prev];
            prev--;
        }

        nums[prev+1] = curr;
    }
}

void print (vector<int> &nums) {
    for (int i: nums) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {23, 0, -78, 23, 9, 41, -2};
    SelectionSort(arr);
    print(arr);

    return 0;
}