#ifndef Stack_H
#define Stack_H

class Node {
private:
    int key;
    int bf; 
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(int k) {
        key = k;
        bf = 0;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    int getKey() { return key; }
    int getBF() { return bf; }
    Node* getLeft() { return left; }
    Node* getRight() { return right; }
    Node* getParent() { return parent; }

    void setKey(int k) { key = k; }
    void setBF(int b) { bf = b; }
    void setLeft(Node* l) { left = l; }
    void setRight(Node* r) { right = r; }
    void setParent(Node* p) { parent = p; }
};

class stack {
private:
    Node** arr;
    int topIndex;
    int capacity;

public:
    stack(int size) {
        capacity = size;
        arr = new Node*[capacity];
        topIndex = -1;
    }

    ~stack() {
        delete[] arr;
    }

    bool push(Node* node) {
        if (isFull()) return false;
        arr[++topIndex] = node;
        return true;
    }

    Node* pop() {
        if (isEmpty()) return nullptr;
        return arr[topIndex--];
    }

    Node* top() {
        if (isEmpty()) return nullptr;
        return arr[topIndex];
    }

    bool isEmpty() { return topIndex == -1; }
    bool isFull() { return topIndex == capacity - 1; }
};


class queue {
private:
    Node** arr;      
    int frontIndex;   
    int rearIndex;    
    int capacity;     
    int count;        

public:
    queue(int size) {
        capacity = size;
        arr = new Node*[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~queue() {
        delete[] arr;
    }

    bool enqueue(Node* node) {
        if (isFull()) return false;
        rearIndex = (rearIndex + 1) % capacity;  
        arr[rearIndex] = node;
        count++;
        return true;
    }

    Node* dequeue() {
        if (isEmpty()) return nullptr;
        Node* item = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;  // circular increment
        count--;
        return item;
    }

    Node* front() {
        if (isEmpty()) return nullptr;
        return arr[frontIndex];
    }

    Node* rear() {
        if (isEmpty()) return nullptr;
        return arr[rearIndex];
    }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    int size() { return count; }
};


#endif