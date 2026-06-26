#include <iostream>
#include <vector>
// #include <utility>
using namespace std;

int partition (vector <int> &arr, int st, int end) {
    int pivot = arr[end];
    int pvtidx = st -1;

    for(int i = st; i < end; i++) {
        if (arr[i] <= pivot) {
            pvtidx++;
            swap(arr[i], arr[pvtidx]);
        }
    }

    pvtidx++;
    swap(arr[pvtidx], arr[end]);
    return pvtidx;
}

void QuickSort(vector<int> &arr, int st, int end) {
    if (st < end) {
        int pvtidx = partition(arr, st, end);
        QuickSort(arr, st, pvtidx - 1); 
        QuickSort(arr, pvtidx+1, end);
    }
}


int main() {
    vector <int> arr = {23,5,3,-8,0,2,-90,56};
    QuickSort(arr, 0, arr.size()-1);

    for (int val: arr) {
        cout << val << " ";
    }
    return 0;
}