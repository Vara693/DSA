#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

class Queue {
    public:
    Node *front;
    Node *rear;

    Queue() {
        front = rear = NULL;
    }

    void push(int val) {
        Node *newnode = new Node(val);

        if(front == NULL) {
            front = rear = newnode;
            return;
        } 
        rear->next = newnode;
        rear = newnode;
        return;
    }

    void pop() {
        if (front == nullptr) {
            cout << "Queue is empty" << endl;
            return;
        }

        Node *temp = front;
        front = front->next;
        temp->next = NULL;
        delete temp;
    }

    int front_ele() {
        if (front == nullptr) {
            return -1;
        }

        return front->data;
    }

    bool isempty() {
        return front == nullptr;
    }

    void print_queue() {
        Node *temp = front;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

};

bool isInteger(const string &s) {
    if (s.empty()) return false;

    for (int i = 0; i < (int)s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main() {
    Queue s;
    bool running = true;
    string input;

    while (running) {
        cout << "\n--- Queue Menu ---\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Front\n";
        cout << "4. Check if Empty\n";
        cout << "5. Print Queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        if (!isInteger(input)) {
            cout << "Invalid input! Please enter a number.\n";
        } else {
            int choice = stoi(input);

            if (choice == 1) {
                cout << "Enter value to enqueue: ";
                getline(cin, input);
                if (isInteger(input)) {
                    int val = stoi(input);
                    s.push(val);
                } else {
                    cout << "Invalid input! Please enter an integer.\n";
                }
            } 
            else if (choice == 2) {
                s.pop();
            } 
            else if (choice == 3) {
                int t = s.front_ele();
                if (t != -1) {
                    cout << "Front element: " << t << endl;
                } else {
                    cout << "Queue is empty" << endl;
                }
            } 
            else if (choice == 4) {
                cout << (s.isempty() ? "Queue is empty" : "Queue is not empty") << endl;
            } 
            else if (choice == 5) {
                s.print_queue();
            } 
            else if (choice == 6) {
                cout << "Exiting program...\n";
                running = false;
            } 
            else {
                cout << "Invalid choice! Try again.\n";
            }
        }
    }

    return 0;
}