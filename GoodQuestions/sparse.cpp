#include <iostream>
using namespace std;

#define MAX 100

// ------------------ ARRAY OPERATIONS ------------------

void traverse(int arr[], int n) {
    cout << "Array elements: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int insertAt(int arr[], int n, int pos, int val) {
    if (pos > n || pos < 0) {
        cout << "Invalid Position!" << endl;
        return n;
    }

    for (int i = n; i > pos; i--)
        arr[i] = arr[i - 1];

    arr[pos] = val;
    return n + 1;
}

int deleteAt(int arr[], int n, int pos) {
    if (pos >= n || pos < 0) {
        cout << "Invalid Position!" << endl;
        return n;
    }

    for (int i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];

    return n - 1;
}

int searchElement(int arr[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}

// ------------------ SPARSE MATRIX ------------------

struct Sparse {
    int row, col, value;
};

void convertToSparse(int mat[][MAX], int r, int c, Sparse sparse[], int &nonZero) {
    nonZero = 0;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (mat[i][j] != 0) {
                sparse[nonZero].row = i;
                sparse[nonZero].col = j;
                sparse[nonZero].value = mat[i][j];
                nonZero++;
            }
        }
    }
}

void printSparse(Sparse sparse[], int nonZero) {
    cout << "\nSparse Matrix (row col value):\n";
    for (int i = 0; i < nonZero; i++)
        cout << sparse[i].row << " " << sparse[i].col << " " << sparse[i].value << endl;
}

// ------------------ MAIN ------------------

int main() {
    int arr[MAX] = {1, 3, 5, 7, 9};
    int n = 5;

    cout << "Initial Array:\n";
    traverse(arr, n);

    n = insertAt(arr, n, 2, 50);
    cout << "After Insertion:\n";
    traverse(arr, n);

    n = deleteAt(arr, n, 3);
    cout << "After Deletion:\n";
    traverse(arr, n);

    int key = 7;
    int pos = searchElement(arr, n, key);
    if (pos != -1)
        cout << "Element found at index: " << pos << endl;
    else
        cout << "Element not found!" << endl;

    // ---------------- SPARSE MATRIX DEMO ----------------
    int r = 3, c = 3;
    int mat[MAX][MAX] = {
        {0, 5, 0},
        {0, 0, 9},
        {2, 0, 0}
    };

    Sparse sparse[MAX];
    int nonZero;

    convertToSparse(mat, r, c, sparse, nonZero);

    printSparse(sparse, nonZero);

    return 0;
}
