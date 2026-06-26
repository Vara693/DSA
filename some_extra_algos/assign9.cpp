#include <iostream>
#include <limits>
using namespace std;

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

class AVL {
private:
    Node* root;

    int height(Node* root) {
        if (root == nullptr) return -1;

        const int MAX_NODES = 50;
        Node* queue[MAX_NODES];
        int front = 0, rear = 0;

        queue[rear++] = root;
        int height = -1;

        while (front < rear) {
            int levelSize = rear - front;
            height++;

            for (int i = 0; i < levelSize; ++i) {
                Node* current = queue[front++];

                if (current->getLeft() != nullptr)
                    queue[rear++] = current->getLeft();

                if (current->getRight() != nullptr)
                    queue[rear++] = current->getRight();
            }
        }

        return height;
    }

    void updateBalance(Node* n) {
        while (n != nullptr) {
            int LH = height(n->getLeft());
            int RH = height(n->getRight());
            n->setBF(LH - RH);
            n = n->getParent();
        }
    }

    Node* rotateLeft(Node* A) {
        Node* B = A->getRight();
        A->setRight(B->getLeft());
        if (B->getLeft() != nullptr) {
            B->getLeft()->setParent(A);
        }
        B->setParent(A->getParent());

        if (A->getParent() == nullptr) {
            root = B;
        } else {
            if (A == A->getParent()->getLeft()) {
                A->getParent()->setLeft(B);
            } else {
                A->getParent()->setRight(B);
            }
        }
        B->setLeft(A);
        A->setParent(B);

        updateBalance(A);
        updateBalance(B);

        return B;
    }

    Node* rotateRight(Node* A) {
        Node* B = A->getLeft();
        A->setLeft(B->getRight());
        if (B->getRight() != nullptr) {
            B->getRight()->setParent(A);
        }
        B->setParent(A->getParent());

        if (A->getParent() == nullptr) {
            root = B;
        } else {
            if (A == A->getParent()->getRight()) {
                A->getParent()->setRight(B);
            } else {
                A->getParent()->setLeft(B);
            }
        }
        B->setRight(A);
        A->setParent(B);

        updateBalance(A);
        updateBalance(B);

        return B;
    }

    void rebalance(Node* n) {
        while (n != nullptr) {
            updateBalance(n);

            if (n->getBF() == 2) {
                if (n->getLeft()->getBF() < 0) {
                    rotateLeft(n->getLeft());
                }
                n = rotateRight(n);
            } 
            else if (n->getBF() == -2) {
                if (n->getRight()->getBF() > 0) {
                    rotateRight(n->getRight());
                }
                n = rotateLeft(n);
            }
            n = n->getParent();
        }
    }

    Node* findMin(Node* n) {
        Node* curr = n;
        while (curr != nullptr && curr->getLeft() != nullptr) {
            curr = curr->getLeft();
        }
        return curr;
    }

public:
    AVL() { root = nullptr; }

    Node* getRoot() { return root; }

    void insert(int key) {
        Node* newNode = new Node(key);

        if (search(key)) return;

        if (root == nullptr) {
            root = newNode;
        } else {
            Node* curr = root;
            Node* par = nullptr;

            while (curr != nullptr) {
                par = curr;
                if (key < curr->getKey()) {
                    curr = curr->getLeft();
                } else {
                    curr = curr->getRight();
                }
            }
            newNode->setParent(par);
            if (key < par->getKey()) {
                par->setLeft(newNode);
            } else {
                par->setRight(newNode);
            }
        }
        rebalance(newNode);
    }

    Node* searchNode(int key) {
        Node* curr = root;
        while (curr != nullptr) {
            if (key == curr->getKey()) return curr;
            curr = (key < curr->getKey() ? curr->getLeft() : curr->getRight());
        }
        return nullptr;
    }

    bool search(int key) { return (searchNode(key) != nullptr); }

    void deleteNode(int key) {
        Node* target = searchNode(key);
        if (target == nullptr) return;

        Node* rebalanceStart = nullptr;
        Node* deleteNodePtr = target;

        // Node has two children
        if (target->getLeft() != nullptr && target->getRight() != nullptr) {
            Node* successor = target->getRight();
            while (successor->getLeft() != nullptr) {
                successor = successor->getLeft();
            }
            target->setKey(successor->getKey());
            deleteNodePtr = successor; 
        }

        //Node has 0 or 1 child
        Node* child = nullptr;
        if (deleteNodePtr->getLeft() != nullptr) {
            child = deleteNodePtr->getLeft();
        } else if (deleteNodePtr->getRight() != nullptr) {
            child = deleteNodePtr->getRight();
        }

        Node* parent = deleteNodePtr->getParent();
        if (parent == nullptr) {
            root = child;
            if (child != nullptr) child->setParent(nullptr);
            rebalanceStart = root;
        } else {
            if (deleteNodePtr == parent->getLeft()) {
                parent->setLeft(child);
            } else {
                parent->setRight(child);
            }
            if (child != nullptr) child->setParent(parent);
            rebalanceStart = parent;
        }

        delete deleteNodePtr;

        if (rebalanceStart != nullptr) {
            rebalance(rebalanceStart);
        }
    }


    void update(int oldKey, int newKey) {
        if (!search(oldKey)) return;
        deleteNode(oldKey);
        insert(newKey);
    }

    void display() {
        Node* stack[50];
        int top = -1;
        Node* curr = root;

        while (curr != nullptr || top >= 0) {
            if (curr != nullptr) {
                top++;
                stack[top] = curr;
                curr = curr->getLeft();
            } else {
                curr = stack[top];
                top--;
                cout << curr->getKey() << "(" << curr->getBF() << ")  ";
                curr = curr->getRight();
            }
        }
        cout << "\n";
    }
};

bool isValidInt(const string& s) {
    if (s.empty()) return false;

    int i = 0;
    if (s[0] == '-' || s[0] == '+') i++;

    if (i == s.length()) return false;

    for (; i < s.length(); ++i) {
        if (!isdigit(s[i])) return false;
    }

    return true;
}

int getInt(string msg) {
    string input;
    int val;
    bool ok = false;

    while (!ok) {
        cout << msg;
        cin >> input;

        if (isValidInt(input)) {
            val = stoi(input); 
            ok = true;
        } else {
            cout << "Invalid input. Enter a valid integer.\n";
        }
    }

    return val;
}



int main() {
    AVL tree;
    int choice, val, newVal;

    cout << "\nAVL Tree (Iterative, No recursion, No break/continue)\n";

    do {
        cout << "\nMENU:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Update\n";
        cout << "4. Delete\n";
        cout << "5. Display\n";
        cout << "6. Exit\n";

        choice = getInt("Enter choice: ");

        if (choice == 1) {
            val = getInt("Enter value: ");
            tree.insert(val);
        } else if (choice == 2) {
            val = getInt("Enter search key: ");
            cout << (tree.search(val) ? "Found\n" : "Not Found\n");
        } else if (choice == 3) {
            val = getInt("Enter existing key: ");
            newVal = getInt("Enter new key: ");
            tree.update(val, newVal);
        } else if (choice == 4) {
            val = getInt("Enter delete key: ");
            tree.deleteNode(val);
        } else if (choice == 5) {
            tree.display();
        }

    } while (choice != 6);

    return 0;
}
