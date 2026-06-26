#include <stdio.h>

#define MAX_SIZE 50

int arr[MAX_SIZE];
int size = 0;

int isValid(int val) {
    return val <=0 || val > 0;
}

void selectionSort() {
    for (int i = 0; i < size - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[idx])
                idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[idx];
        arr[idx] = temp;
    }
    printf("Array sorted.\n");
}

int binarySearch(int target) {
    int left = 0, right = size - 1;
    int result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}


void insertElement(int value) {
    if (size >= MAX_SIZE) {
        printf("Array is full.\n");
        return;
    }
    arr[size++] = value;
    printf("Element inserted.\n");
}

void deleteElement(int value) {
    int index = -1;
    int found = 0;
    for (int i = 0; i < size && found == 0; i++) {
        if (arr[i] == value) {
            index = i;
            found = 1;
        }
    }
    if (index == -1) {
        printf("Element not found.\n");
        return;
    }
    for (int i = index; i < size - 1; i++)
        arr[i] = arr[i + 1];
    size--;
    printf("Element deleted.\n");
}

void displayArray() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Enter array\n");
        printf("2. Display array\n");
        printf("3. Sort array (Selection Sort)\n");
        printf("4. Search element (Binary Search)\n");
        printf("5. Insert element\n");
        printf("6. Delete element\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            printf("Enter number of elements (max %d): ", MAX_SIZE);
            if (scanf("%d", &size) != 1 || size <= 0 || size > MAX_SIZE) {
                printf("Invalid size.\n");
                while (getchar() != '\n');
                size = 0;
                continue;
            }

            printf("Enter %d positive integers:\n", size);
            for (int i = 0; i < size; i++) {
                if (scanf("%d", &arr[i]) != 1 || !isValid(arr[i])) {
                    printf("Invalid input. Only positive numbers allowed.\n");
                    while (getchar() != '\n');
                    size = 0;
                    break;
                }
            }
        }

        else if (choice == 2) {
            displayArray();
        }

        else if (choice == 3) {
            selectionSort();
        }

        else if (choice == 4) {
            int target;
            printf("Enter value to search: ");
            if (scanf("%d", &target) != 1 || !isValid(target)) {
                printf("Invalid input. Only positive numbers allowed.\n");
                while (getchar() != '\n');
                continue;
            }
            int result = binarySearch(target);
            if (result != -1)
                printf("Element found at index %d\n", result);
            else
                printf("Element not found.\n");
        }

        else if (choice == 5) {
            int value;
            printf("Enter value to insert: ");
            if (scanf("%d", &value) != 1 || !isValid(value)) {
                printf("Invalid input. Only positive numbers allowed.\n");
                while (getchar() != '\n');
                continue;
            }
            insertElement(value);
        }

        else if (choice == 6) {
            int value;
            printf("Enter value to delete: ");
            if (scanf("%d", &value) != 1 || !isValid(value)) {
                printf("Invalid input. Only positive numbers allowed.\n");
                while (getchar() != '\n');
                continue;
            }
            deleteElement(value);
        }

        else if (choice == 7) {
            printf("Exiting program.\n");
        }

        else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
