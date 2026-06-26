#ifndef Queue_H
#define Queue_H

class Node {
    private:
    int data;
    Node* left;
    Node* right;
    
    public:
    Node(int value) {
        data = value;
        left = right = nullptr; 
    }

    int getData() const { return data;}
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }

    void setLeft(Node* node) { left = node; }
    void setRight(Node* node) { right = node; }
    void setData(int value) { data = value; }
};

class queue {
private:
    Node** arr;
    int front;
    int rear;
    int capacity;

public:
    queue(int size) {
        capacity = size;
        arr = new Node*[capacity];
        front = 0;
        rear = -1;
    }

    ~queue() {
        delete[] arr;
    }

    bool push(Node* node) {
        if (isFull()) return false;
        arr[++rear] = node;
        return true;
    }

    Node* pop() {
        if (isEmpty()) return nullptr;
        Node* temp = arr[front++];
        if (front > rear) front = 0; rear = -1;
        return temp;
    }

    Node* frontIdx() {
        if (isEmpty()) return nullptr;
        return arr[front];
    }

    bool isEmpty() { return front > rear; }
    bool isFull() const { return rear == capacity - 1; }
};

#endif