#include <iostream>
using namespace std;

class node {
    public:
    int data;
    node *next;

    
    node(int val) {
        data = val;
        next = NULL;
    }
};

class queue {
    node *rear;
    node *front;

    public:
    queue() {
        front = rear = NULL;
    }

    void push (int val) {
        node *newnode = new node(val);
        if (front == NULL) {
            front = rear = newnode;
        } else {
            rear->next = newnode;
            rear = newnode;
        }
    }

    void pop() {
        if (front == NULL) {
            cout << "Queue is empty" << endl;
        } else {
            node *temp = front;
            front = front->next;
            delete temp;
        }
    }

    void print() {
        node *temp = front;
        while(temp!= NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void peak() {
        cout << front->data << endl;
    }
};
int main() {
    queue q;
    q.push(1);
    q.push(1);
    q.push(4);
    q.push(3);
    q.pop();
    q.peak();
    q.pop();
    q.peak();
    q.print();

    return 0;
}