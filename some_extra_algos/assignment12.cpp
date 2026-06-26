#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

int readInt(const string& prompt) {
    string input;
    int val = 0;
    bool valid = false;

    while (!valid) {
        cout << prompt;
        getline(cin, input);

        // Trim whitespace
        size_t start = input.find_first_not_of(' ');
        size_t end = input.find_last_not_of(' ');
        if (start == string::npos) {
            cout << "Invalid input. Please enter a number.\n";
        } else {
            input = input.substr(start, end - start + 1);
            bool isNegative = false;
            bool allDigits = true;
            size_t begin = 0;

            if (!input.empty() && input[0] == '-') {
                isNegative = true;
                if (input.length() == 1) {
                    allDigits = false;
                } else {
                    begin = 1;
                }
            }

            size_t i = begin;
            while (i < input.length() && allDigits) {
                if (!isdigit(input[i])) {
                    allDigits = false;
                }
                i++;
            }

            if (allDigits) {
                try {
                    val = stoi(input);
                    valid = true;
                } catch (...) {
                    cout << "Error: Integer out of range. Try again.\n";
                }
            } else {
                cout << "Invalid input. Please enter a valid integer.\n";
            }
        }
    }
    return val;
}

int partition(vector<int>& arr, int st, int end) {
    int pivot = arr[end];
    int pvtidx = st - 1;

    for (int i = st; i < end; i++) {
        if (arr[i] <= pivot) {
            pvtidx++;
            swap(arr[i], arr[pvtidx]);
        }
    }

    pvtidx++;
    swap(arr[pvtidx], arr[end]);
    return pvtidx;
}

void QuickSort(vector<int>& arr, int st, int end) {
    if (st < end) {
        int pvtidx = partition(arr, st, end);
        QuickSort(arr, st, pvtidx - 1);
        QuickSort(arr, pvtidx + 1, end);
    }
}

void displayArray(const vector<int>& arr) {
    if (arr.empty()) {
        cout << "[Empty Array]\n";
    } else {
        cout << "Array: ";
        for (int val : arr) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

void inputArray(vector<int>& arr) {
    arr.clear();
    int n = readInt("Enter number of elements: ");
    int i = 0;
    while (i < n) {
        int val = readInt("Enter element #" + to_string(i + 1) + ": ");
        arr.push_back(val);
        i++;
    }
}

int main() {
    vector<int> arr;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\n===== QuickSort Menu =====\n";
        cout << "1. Input array\n";
        cout << "2. Display array\n";
        cout << "3. Sort array using QuickSort\n";
        cout << "4. Exit\n";

        int choice = readInt("Choose an option (1-4): ");
        if (choice == 1) {
            inputArray(arr);
        } else if (choice == 2) {
            displayArray(arr);
        } else if (choice == 3) {
            if (arr.empty()) {
                cout << "Array is empty. Please input elements first.\n";
            } else {
                QuickSort(arr, 0, arr.size() - 1);
                cout << "Array sorted successfully.\n";
            }
        } else if (choice == 4) {
            exitProgram = true;
        } else {
            cout << "Invalid choice. Please select between 1 and 4.\n";
        }
    }

    cout << "Program terminated.\n";
    return 0;
}
