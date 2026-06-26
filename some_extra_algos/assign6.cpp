#include <iostream>
#include <queue>
#include <string>
#include <cctype>
#include <stack>
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

class BinaryTree {
private:
    Node* root;

    void inorder(Node* root) {
        stack<Node*> st;
        Node* curr = root;

        while (curr != nullptr || !st.empty()) {
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

    Node* search(Node* node, int value) {
        if (!node) return nullptr;
        if (node->getData() == value) return node;
        Node* leftSearch = search(node->getLeft(), value);
        if (leftSearch) return leftSearch;
        return search(node->getRight(), value);
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return nullptr;

        if (!root->getLeft() && !root->getRight()) {
            if (root->getData() == key) {
                delete root;
                return nullptr;
            }
            return root;
        }

        queue<Node*> q;
        q.push(root);
        Node* keyNode = nullptr;
        Node* temp;

        while (!q.empty()) {
            temp = q.front();
            q.pop();

            if (temp->getData() == key)
                keyNode = temp;

            if (temp->getLeft()) {
                q.push(temp->getLeft());
            }
            if (temp->getRight()) {
                q.push(temp->getRight());
            }
        }

        if (keyNode) {
            int deepestVal = temp->getData();
            deleteDeepest(root, temp);
            keyNode->setData(deepestVal);
            cout << "Deleted node with value " << key << ".\n";
        } else {
            cout << "Value not found in the tree.\n";
        }
        return root;
    }

    void deleteDeepest(Node* root, Node* dNode) {
        if (!root || !dNode) return;

        // if (root == dNode) {
        //     delete root;
        //     return;
        // }

        queue<Node*> q;
        q.push(root);

        Node* temp;
        while (!q.empty()) {
            temp = q.front();
            q.pop();

            if (temp->getLeft()) {
                if (temp->getLeft() == dNode) {
                    delete temp->getLeft();
                    temp->setLeft(nullptr);
                    return;
                } else q.push(temp->getLeft());
            }

            if (temp->getRight()) {
                if (temp->getRight() == dNode) {
                    delete temp->getRight();
                    temp->setRight(nullptr);
                    return;
                } else q.push(temp->getRight());
            }
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            if (!temp->getLeft()) {
                temp->setLeft(newNode);
                return;
            } else q.push(temp->getLeft());

            if (!temp->getRight()) {
                temp->setRight(newNode);
                return;
            } else q.push(temp->getRight());
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

    void update(int oldVal, int newVal) {
        Node* node = search(root, oldVal);
        if (node) {
            node->setData(newVal);
            cout << "Updated value " << oldVal << " to " << newVal << ".\n";
        } else {
            cout << "Value " << oldVal << " not found.\n";
        }
    }

    void remove(int value) {
        root = deleteNode(root, value);
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

        bool valid = true;
        if (input.empty()) valid = false;
        for (int i = 0; i < input.size(); i++) {
            if (!isdigit(input[i]) && !(i == 0 && input[i] == '-') && valid) {
                valid = false;
            }
        }

        if (valid) {
            try {
                return stoi(input);
            } catch (...) {
                cout << "Error: Integer out of range. Try again.\n";
            }
        } else {
            cout << "Invalid input. Please enter only digits.\n";
        }
    }
}

int main() {
    BinaryTree tree;
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
