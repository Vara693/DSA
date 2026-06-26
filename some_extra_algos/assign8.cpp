#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Node {
private:
    int data;
    Node* left;
    Node* right;
    bool lthread; 
    bool rthread;

public:
    Node(int value) {
        data = value;
        left = right = nullptr; 
        lthread = rthread = false;
    }

    int getData() const { return data; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }
    bool isLThread() const { return lthread; }
    bool isRThread() const { return rthread; }

    void setData(int value) { data = value; }
    void setLeft(Node* node) { left = node; }
    void setRight(Node* node) { right = node; }
    void setLThread(bool b) { lthread = b; }
    void setRThread(bool b) { rthread = b; }
};


class ThreadedBT {
private:
    Node* root;

    Node* leftMost(Node* node) const {
        Node* curr = node;
        if (!curr) return curr;
        while (curr->isLThread() == false && curr->getLeft()) {
            curr = curr->getLeft();
        }
        return curr;
    }

    Node* inorderSuccessor(Node* node) const {
        if (!node) return node;
        if (node->isRThread() == true) {
            return node->getRight();
        } else {
            Node* q = node->getRight();
            return leftMost(q);
        }
    }

    Node* searchNode(int key) const {
        Node* curr = root;
        while (curr) {
            if (key == curr->getData()) {
                return curr;
            } else if (key < curr->getData()) {
                if (curr->isLThread() == false) {
                    curr = curr->getLeft();
                } else {
                    curr = nullptr;
                }
            } else {
                if (curr->isRThread() == false) {
                    curr = curr->getRight();
                } else {
                    curr = nullptr;
                }
            }
        }
        return nullptr;
    }

    Node* inorderPredecessor(Node* node) const {
        if (!node) return node;
        if (node->isLThread() == true) {
            return node->getLeft();
        } else {
            Node* rightMost = node->getLeft();
            while (rightMost->isRThread() == false && rightMost) {
                rightMost = rightMost->getRight();
            }
            return rightMost;
        }
    }

public:
    ThreadedBT() : root(nullptr) {}

    bool insert(int key) {
        Node* newNode = new Node(key);
        if (!newNode) return false;

        if (!root) {
            root = newNode;
            return true;
        }

        Node* cur = root;
        Node* parent = nullptr;
        bool insertLeft = false;

        while (cur != nullptr) {
            parent = cur;

            if (key == cur->getData()) {
                delete newNode;
                return false; // duplicate
            } 
            else if (key < cur->getData()) {
                if (!cur->isLThread()) {
                    cur = cur->getLeft();
                } else {
                    insertLeft = true;
                    cur = nullptr;
                }
            } 
            else {
                if (!cur->isRThread()) {
                    cur = cur->getRight();
                } else {
                    insertLeft = false;
                    cur = nullptr;
                }
            }
        }

        if (insertLeft) {
            // Attach as left child
            newNode->setLeft(parent->getLeft());  // inherit predecessor
            newNode->setRight(parent);            // successor = parent

            // If predecessor exists (not null), it's a thread, so link it
            if (newNode->getLeft() != nullptr) {
                newNode->setLThread(true);
                Node* pred = newNode->getLeft();
                if (pred->isRThread())
                    pred->setRight(newNode);
            } else {
                newNode->setLThread(false);
            }

            // right always a thread to parent
            newNode->setRThread(true);
            parent->setLThread(false);
            parent->setLeft(newNode);
        }
        else {
            // Attach as right child
            newNode->setRight(parent->getRight()); // inherit successor
            newNode->setLeft(parent);              // predecessor = parent

            if (newNode->getRight() != nullptr) {
                newNode->setRThread(true);
                Node* succ = newNode->getRight();
                if (succ->isLThread())
                    succ->setLeft(newNode);
            } else {
                newNode->setRThread(false);
            }

            newNode->setLThread(true);
            parent->setRThread(false);
            parent->setRight(newNode);
        }

        return true;
    }



    void inorder() const {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }

        // Start from the leftmost node
        Node* cur = leftMost(root);

        while (cur != nullptr) {
            cout << cur->getData() << " ";

            // If node has a successor thread, follow it directly
            if (cur->isRThread() == true) {
                cur = cur->getRight();
            }
            else {
                // Otherwise, move to the leftmost of its right subtree
                cur = leftMost(cur->getRight());
            }
        }

        cout << "\n";
    }


    bool search(int key) const {
        Node* res = searchNode(key);
        return (res != nullptr);
    }

    bool update(int oldVal, int newVal) {
        if (oldVal == newVal) return true;
        Node* target = searchNode(oldVal);
        if (target == nullptr) return false;

        Node* already = searchNode(newVal);
        if (already != nullptr) {
            return false;
        }

        bool removed = deleteNode(oldVal);
        if (removed == false) return false;
        bool inserted = insert(newVal);
        if (inserted == false) {
            insert(oldVal);
            return false;
        }
        return true;
    }

    bool deleteNode(int key) {
        if (!root) return false;

        Node* parent = nullptr;
        Node* cur = root;

        while (cur != nullptr && cur->getData() != key) {
            parent = cur;

            if (key < cur->getData()) {
                if (!cur->isLThread())
                    cur = cur->getLeft();
                else
                    cur = nullptr;
            } else {
                if (!cur->isRThread())
                    cur = cur->getRight();
                else
                    cur = nullptr;
            }
        }

        if (cur == nullptr) return false;

        // Node with two children
        if (!cur->isLThread() && !cur->isRThread()) {
            Node* succParent = cur;
            Node* succ = cur->getRight();

            while (!succ->isLThread()) {
                succParent = succ;
                succ = succ->getLeft();
            }

            cur->setData(succ->getData());

            parent = succParent;
            cur = succ;
        }

        // Node is a leaf
        if (cur->getLeft() == nullptr && cur->getRight() == nullptr) {
            if (parent == nullptr) {
                delete cur;
                root = nullptr;
                return true;
            } else {
                if (parent->getLeft() == cur) {
                    parent->setLeft(nullptr);
                    parent->setLThread(false);
                } else {
                    parent->setRight(nullptr);
                    parent->setRThread(false);
                }
                delete cur;
                return true;
            }
        }

        // Node has only a left child
        if (!cur->isLThread() && (cur->isRThread() || cur->getRight() == nullptr)) {
            Node* child = cur->getLeft();

            Node* rightMost = child;
            while (!rightMost->isRThread() && rightMost->getRight() != nullptr) {
                rightMost = rightMost->getRight();
            }
            rightMost->setRight(cur->getRight());

            if (parent == nullptr) {
                root = child;
            } else {
                if (parent->getLeft() == cur)
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            }

            delete cur;
            return true;
        }

        // Node has only a right child
        if (!cur->isRThread() && (cur->isLThread() || cur->getLeft() == nullptr)) {
            Node* child = cur->getRight();

            Node* leftMostNode = child;
            while (!leftMostNode->isLThread() && leftMostNode->getLeft() != nullptr) {
                leftMostNode = leftMostNode->getLeft();
            }
            leftMostNode->setLeft(cur->getLeft());

            if (parent == nullptr) {
                root = child;
            } else {
                if (parent->getLeft() == cur)
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            }

            delete cur;
            return true;
        }

        // Fix leftmost and rightmost boundary threads after deletion
        if (root != nullptr) {
            Node* leftmost = root;
            while (leftmost && !leftmost->isLThread() && leftmost->getLeft() != nullptr)
                leftmost = leftmost->getLeft();
            if (leftmost) {
                leftmost->setLeft(nullptr);
                leftmost->setLThread(false);
            }

            Node* rightmost = root;
            while (rightmost && !rightmost->isRThread() && rightmost->getRight() != nullptr)
                rightmost = rightmost->getRight();
            if (rightmost) {
                rightmost->setRight(nullptr);
                rightmost->setRThread(false);
            }
        }

        return false;
    }

};

int readInt(const string& prompt) {
    string input;
    int val = 0;
    bool valid = false;

    while (!valid) {
        cout << prompt;
        getline(cin, input);

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


int main() {
    ThreadedBT tree;
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "------------------Threaded Binary Tree------------------\n";
        cout << "1. Insert\n";
        cout << "2. Inorder traversal (print)\n";
        cout << "3. Search\n";
        cout << "4. Update value\n";
        cout << "5. Delete\n";
        cout << "6. Exit\n";

        int choice = readInt("Enter choice (1-6): ");

        if (choice == 1) {
            int v = readInt("Enter integer to insert: ");
            bool ok = tree.insert(v);
            if (ok)
                cout << "Inserted " << v << ".\n";
            else
                cout << "Value " << v << " already exists. Insert failed.\n";

        } else if (choice == 2) {
            cout << "Inorder: ";
            tree.inorder();

        } else if (choice == 3) {
            int v = readInt("Enter integer to search: ");
            bool found = tree.search(v);
            if (found)
                cout << "Found " << v << " in tree.\n";
            else
                cout << v << " not found.\n";

        } else if (choice == 4) {
            int oldv = readInt("Enter existing value to update: ");
            int newv = readInt("Enter new integer value: ");
            bool ok = tree.update(oldv, newv);
            if (ok)
                cout << "Updated " << oldv << " -> " << newv << ".\n";
            else
                cout << "Update failed. Either " << oldv << " not found or " << newv << " exists.\n";

        } else if (choice == 5) {
            int v = readInt("Enter integer to delete: ");
            bool ok = tree.deleteNode(v);
            if (ok)
                cout << "Deleted " << v << " from tree.\n";
            else
                cout << v << " not found. Delete failed.\n";

        } else if (choice == 6) {
            exitFlag = true;

        } else {
            cout << "Invalid choice. Choose 1-6.\n";
        }
    }

    cout << "Goodbye.\n";
    return 0;
}

