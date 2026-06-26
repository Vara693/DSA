#include <iostream>
#include <limits>
#include <string>
#include <cctype>

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

class stack {

    public:
    Node *head;

    stack() {
        head = NULL;
    }

    void push(int val) {
        Node *newnode = new Node(val);

        if(head == NULL) {
            head = newnode;
            return;
        } else {
            newnode->next = head;
            head = newnode;
            return;
        }
    }

    void pop() {
        if (head == nullptr) {
            cout << "Stack is empty" << endl;
            return;
        } else {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;
            return;
        }
    }

    int top() {
        if (head == nullptr) {
            return -1;
        } 
        return head->data;
    }

    bool isempty() {
        return head == nullptr;
    }

    void print_stack() {
        Node *temp = head;
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
    stack s;
    bool running = true;
    string input;

    while (running) {
        cout << "\n--- Stack Menu ---\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Check if Empty\n";
        cout << "5. Print Stack\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        if (!isInteger(input)) {
            cout << "Invalid input! Please enter a number.\n";
        } else {
            int choice = stoi(input);

            if (choice == 1) {
                cout << "Enter value to push: ";
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
                int t = s.top();
                if (t != -1) {
                    cout << "Top element: " << t << endl;
                } else {
                    cout << "Stack is empty" << endl;
                }
            } 
            else if (choice == 4) {
                cout << (s.isempty() ? "Stack is empty" : "Stack is not empty") << endl;
            } 
            else if (choice == 5) {
                s.print_stack();
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