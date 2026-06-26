#include <iostream>
#include <vector>
using namespace std;

class Stack {
private:
    int* arr;
    int topIndex;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    int push(int val) {
        if (isFull()) {
            // cout << "Stack Overflow\n";
            return 0;
        }
        arr[++topIndex] = val;
        return 1;
    }

    int pop() {
        if (isEmpty()) {
            // cout << "Stack Underflow\n";
            return 0;
        }
        topIndex--;
        return 1;
    }

    int top() {
        if (isEmpty()) {
            // cout << "Stack is empty\n";
            return 0; 
        }
        return arr[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    bool isFull() {
        return topIndex == capacity - 1;
    }
};


class Queue {
private:
    int* arr;
    int front;
    int rear;
    int capacity;

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    int push(int val) {
        if (isFull()) {
            // cout << "Queue Overflow\n";
            return 0;
        }
        arr[++rear] = val;
        return 1;
    }

    int pop() {
        if (isEmpty()) {
            // cout << "Queue Underflow\n";
            return 0;
        }
        front++;
        return 1;
    }

    int front_ele() {
        if (isEmpty()) {
            // cout << "Queue is empty\n";
            return 0; 
        }
        return arr[front];
    }

    bool isEmpty() {
        return front > rear;
    }

    bool isFull() {
        return rear == capacity - 1;
    }
};

bool getValidInteger(int &num) {
    string input;
    getline(cin, input);

    if (input.find(' ') != string::npos) {
        cout << "Spaces are not allowed.\n";
        return false;
    }
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (!isdigit(c) && !(c == '-' && i == 0)) {
            cout << "Invalid input. Please enter a valid integer.\n";
            return false;
        }
    }

    try {
        num = stoi(input);
    } catch (...) {
        cin.clear();
        cout << "Invalid number format.\n";
        return false;
    }
    return true;
}

int main() {
    int stackSize = 0, queueSize = 0;
    int validInput = 0;

    cout << "Enter Stack size: ";
    while (!validInput) {
        if (getValidInteger(stackSize) && stackSize > 0) {
            validInput = 1;
        } else {
            cout << "Enter a positive integer for size: ";
        }
    }

    validInput = 0;
    cout << "Enter Queue size: ";
    while (!validInput) {
        if (getValidInteger(queueSize) && queueSize > 0) {
            validInput = 1;
        } else {
            cout << "Enter a positive integer for size: ";
        }
    }

    Stack s(stackSize);
    Queue q(queueSize);

    int mainChoice = 0;
    int subChoice = 0;
    int val = 0;
    int running = 1;

    while (running == 1) {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Work with Stack\n";
        cout << "2. Work with Queue\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int validMainInput = getValidInteger(mainChoice);
        if (validMainInput == 0) mainChoice = -1;

        if (mainChoice == 1) {
            int inStackMenu = 1;
            while (inStackMenu == 1) {
                cout << "\n------ STACK MENU ------\n";
                cout << "1. Push\n";
                cout << "2. Pop\n";
                cout << "3. Display Top\n";
                cout << "4. Check if Empty\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";

                if (!getValidInteger(subChoice)) {
                    subChoice = 0;
                }

                if (subChoice == 1) {
                    cout << "Enter value to push: ";
                    if (getValidInteger(val)) {
                        int res = s.push(val);
                        if (res == 1)
                            cout << "Pushed successfully.\n";
                        else
                            cout << "Stack Overflow.\n";
                    }
                } else if (subChoice == 2) {
                    int res = s.pop();
                    if (res == 1)
                        cout << "Popped successfully.\n";
                    else
                        cout << "Stack Underflow.\n";
                } else if (subChoice == 3) {
                    if (!s.isEmpty())
                        cout << "Top element: " << s.top() << "\n";
                    else
                        cout << "Stack is empty.\n";
                } else if (subChoice == 4) {
                    if (s.isEmpty())
                        cout << "Stack is empty.\n";
                    else
                        cout << "Stack is not empty.\n";
                } else if (subChoice == 5) {
                    inStackMenu = 0;
                } else {
                    cout << "Invalid choice.\n";
                }
            }
        } else if (mainChoice == 2) {
            int inQueueMenu = 1;
            while (inQueueMenu == 1) {
                cout << "\n------ QUEUE MENU ------\n";
                cout << "1. Enqueue (Push)\n";
                cout << "2. Dequeue (Pop)\n";
                cout << "3. Display Front\n";
                cout << "4. Check if Empty\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";

                if (!getValidInteger(subChoice)) {
                    subChoice = 0;
                }

                if (subChoice == 1) {
                    cout << "Enter value to enqueue: ";
                    if (getValidInteger(val)) {
                        int res = q.push(val);
                        if (res == 1)
                            cout << "Enqueued successfully.\n";
                        else
                            cout << "Queue Overflow.\n";
                    }
                } else if (subChoice == 2) {
                    int res = q.pop();
                    if (res == 1)
                        cout << "Dequeued successfully.\n";
                    else
                        cout << "Queue Underflow.\n";
                } else if (subChoice == 3) {
                    if (!q.isEmpty())
                        cout << "Front element: " << q.front_ele() << "\n";
                    else
                        cout << "Queue is empty.\n";
                } else if (subChoice == 4) {
                    if (q.isEmpty())
                        cout << "Queue is empty.\n";
                    else
                        cout << "Queue is not empty.\n";
                } else if (subChoice == 5) {
                    inQueueMenu = 0;
                } else {
                    cout << "Invalid choice.\n";
                }
            }
        } else if (mainChoice == 3) {
            cout << "Exiting program.\n";
            running = 0;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}