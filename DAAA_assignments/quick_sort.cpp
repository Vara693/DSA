#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void swapped(int *a, int *b) {
    int temp = *a;
    *a=*b;
    *b=temp;
}

int partition (int arr[], int st, int end) {
    int pivot = arr[end];
    int idx = st-1;

    for (int i=st; i<end; i++) {
        if (arr[i] < pivot) {
            idx++;
            swapped(&arr[i], &arr[idx]);
        }
    }

    idx++;
    swapped(&arr[end], &arr[idx]);
    return idx;
}


void quickSort(int arr[], int st, int end) {
    if (st < end) {
        int pivot = partition(arr, st, end);
        quickSort(arr, st, pivot-1);
        quickSort(arr, pivot+1, end);
    }
}
int main() {
    int arr[] = {8, 3,1,27,7,0,500, 10,2};
    int n= 7;
    quickSort(arr, 0, n-1);
    for (int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}