#include <iostream>
#include <string>
using namespace std;

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


class BinarySearchTree {
    Node* root;

    Node* insert(Node* root, int value, bool &inserted) {
        if (!root) {
            inserted = true;
            return new Node(value);
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->getData()) {
                current = current->getLeft();
            } else if (value > current->getData()) {
                current = current->getRight();
            } else {
                inserted = false;
                return root;
            }
        }

        Node* newNode = new Node(value);
        if (value < parent->getData()) {
            parent->setLeft(newNode);
        } else {
            parent->setRight(newNode);
        }

        inserted = true;
        return root;
    }


    bool search(Node* node, int value) {
        Node* current = node;

        while (current) {
            int data = current->getData();
            if (value == data) {
                return true;
            } else if (value < data) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }

        return false;
    }

    void inorder(Node* root) {
        stack st(20);
        Node* curr = root;

        while (curr != nullptr || !st.isEmpty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->getLeft();
            }

            curr = st.top();
            st.pop();

            cout << curr->getData() << " ";
            curr = curr->getRight();
        }
    }

    Node* findMin(Node* node) {
        while (node && node->getLeft())
            node = node->getLeft();
        return node;
    }

    Node* remove(Node* root, int value) {
        Node* current = root;
        Node* parent = nullptr;

        while (current && current->getData() != value) {
            parent = current;
            if (value < current->getData()) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }

        if (!current) return root;
        Node* child = nullptr;
        if (!current->getLeft() || !current->getRight()) {
            child = current->getLeft();
            if (!child) {
                child = current->getRight();
            }

            if (!parent) {
                delete current;
                return child;
            }

            if (parent->getLeft() == current) {
                parent->setLeft(child);
            } else {
                parent->setRight(child);
            }

            delete current;
        } else {
            Node* successorParent = current;
            Node* successor = current->getRight();

            while (successor->getLeft()) {
                successorParent = successor;
                successor = successor->getLeft();
            }

            current->setData(successor->getData());
            Node* successorChild = successor->getRight();
            if (successorParent->getLeft() == successor) {
                successorParent->setLeft(successorChild);
            } else {
                successorParent->setRight(successorChild);
            }

            delete successor;
        }

        return root;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        bool inserted = false;
        root = insert(root, value, inserted);
        if (!inserted) {
            cout << "Value already exists in the tree.\n";
        }
    }

    void display() {
        if (!root)
            cout << "Tree is empty.\n";
        else {
            cout << "Inorder Traversal: ";
            inorder(root);
            cout << "\n";
        }
    }

    void update(int oldValue, int newValue) {
        if (search(root, oldValue)) {
            root = remove(root, oldValue);
            insert(newValue);
            cout << "Updated value " << oldValue << " to " << newValue << ".\n";
        } else {
            cout << "Value " << oldValue << " not found in the tree.\n";
        }
    }

    void remove(int value) {
        if (search(root, value)) {
            root = remove(root, value);
            cout << "Deleted " << value << " from tree.\n";
        } else {
            cout << "Value not found in the tree.\n";
        }
    }

    void searchValue(int value) {
        if (search(root, value))
            cout << "Value " << value << " found in tree.\n";
        else
            cout << "Value " << value << " not found.\n";
    }
};

int getValidatedInt() {
    string input;
    while (true) {
        cout << "(an integer): ";
        cin >> input;

        if (input.empty()) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        bool valid = true;
        size_t start = 0;

        if (input[0] == '-') {
            if (input.length() == 1) {
                valid = false;
            } else {
                start = 1;
            }
        }

        for (size_t i = start; i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }

        if (valid) {
            try {
                return stoi(input);
            } catch (...) {
                cout << "Error: Integer out of range. Try again.\n";
            }
        } else {
            cout << "Invalid input. Please enter a valid integer.\n";
        }
    }
}

int main() {
    BinarySearchTree tree;
    int choice;

    while (true) {
        cout << "\n=== Binary Tree CRUD Menu ===\n";
        cout << "1. Insert\n2. Display\n3. Search\n4. Update\n5. Delete\n6. Exit\n";
        cout << "Enter choice";

        choice = getValidatedInt();

        if (choice == 1) {
            int value = getValidatedInt();
            tree.insert(value);
        } else if (choice == 2) {
            tree.display();
        } else if (choice == 3) {
            int value = getValidatedInt();
            tree.searchValue(value);
        } else if (choice == 4) {
            cout << "Enter old value: ";
            int oldVal = getValidatedInt();
            cout << "Enter new value: ";
            int newVal = getValidatedInt();
            tree.update(oldVal, newVal);
        } else if (choice == 5) {
            int value = getValidatedInt();
            tree.remove(value);
        } else if (choice == 6) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
