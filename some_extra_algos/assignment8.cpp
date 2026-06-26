#include <iostream>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
    int data;
    Node* left;
    Node* right;
    bool rthread;

public:
    Node(int val) : data(val), left(nullptr), right(nullptr), rthread(false) {}

    int getData() const { return data; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }
    bool isRThreaded() const { return rthread; }

    void setData(int val) { data = val; }
    void setLeft(Node* node) { left = node; }
    void setRight(Node* node) { right = node; }
    void setRThread(bool state) { rthread = state; }
};

class ThreadedBT {
private:
    Node* root;

    Node* find_successor(Node* node) const {
        Node* curr = node->getRight();
        while (curr && !curr->isRThreaded() && curr->getLeft()) {
            curr = curr->getLeft();
        }
        return curr;
    }

    Node* find_predecessor(Node* node) const {
        if (!node || !node->getLeft()) return nullptr;
        Node* curr = node->getLeft();
        while (curr && curr->getRight() && !curr->isRThreaded()) {
            curr = curr->getRight();
        }
        return curr;
    }

public:
    ThreadedBT() : root(nullptr) {}
    ~ThreadedBT() { destroyTree(root); }

    bool insert(int key) {
        if (!root) {
            root = new Node(key);
            return true;
        }

        Node* current = root;
        Node* parent = nullptr;
        bool inserted = false;

        while (!inserted && current) {
            parent = current;
            if (key < current->getData()) {
                current = current->getLeft();
            } else if (key > current->getData()) {
                if (current->isRThreaded()) {
                    current = nullptr;
                } else {
                    current = current->getRight();
                }
            } else {
                return false;
            }
        }

        Node* newNode = new Node(key);
    
    
        if (key < parent->getData()) {
            parent->setLeft(newNode);
            newNode->setRThread(true);
            newNode->setRight(parent);
        } else {
            newNode->setRThread(parent->isRThreaded());
            newNode->setRight(parent->getRight());

            parent->setRThread(false);
            parent->setRight(newNode);
        }
        return true;
    }

    Node* search(int key) const {
        Node* current = root;
        Node* found_node = nullptr;

        while (current) {
            if (key == current->getData()) {
                found_node = current;
                current = nullptr;
            } else if (key < current->getData()) {
                current = current->getLeft();
            } else {
                if (current->isRThreaded()) {
                    current = nullptr;
                } else {
                    current = current->getRight();
                }
            }
        }
        return found_node;
    }

    bool update(int old_key, int new_key) {
        if (search(new_key)) {
            cout << "Modification failed: New key (" << new_key << ") already exists." << endl;
            return false;
        }
        if (remove(old_key)) {
            return insert(new_key);
        }
        return false;
    }

    bool remove(int key) {
        Node* current = root;
        Node* parent = nullptr;
        bool is_left_child = false;
        bool found = false;

        while (current && !found) {
            if (key == current->getData()) {
                found = true;
            } else {
                parent = current;
                if (key < current->getData()) {
                    current = current->getLeft();
                    is_left_child = true;
                } else {
                    is_left_child = false;
                    if (current->isRThreaded()) {
                        current = nullptr;
                    } else {
                        current = current->getRight();
                    }
                }
            }
        }

        if (!found) return false; 

        Node* node_to_delete = current;
        Node* new_child = nullptr;
        bool delete_completed = false;

        while (!delete_completed) {
            
            // NO children
            if (!node_to_delete->getLeft() && (node_to_delete->isRThreaded() || !node_to_delete->getRight())) {
                Node* predecessor = find_predecessor(node_to_delete);
                Node* successor = node_to_delete->getRight(); 

                if (predecessor) {
                    predecessor->setRight(successor);
                }
                new_child = nullptr;
                

                if (!parent) {
                    root = nullptr;
                } else if (is_left_child) {
                    parent->setLeft(new_child);
                } else {
                    parent->setRThread(node_to_delete->isRThreaded());
                    parent->setRight(node_to_delete->getRight());
                }
                delete node_to_delete;
                delete_completed = true;
            }

            // only ONE child
            if (!delete_completed && ((!node_to_delete->getLeft() && node_to_delete->getRight() && !node_to_delete->isRThreaded()) || (node_to_delete->getLeft() && (node_to_delete->isRThreaded() || !node_to_delete->getRight())))) {
                if (node_to_delete->getLeft()) {
                    new_child = node_to_delete->getLeft();

                    Node* pred = find_predecessor(node_to_delete);
                    Node* succ = node_to_delete->getRight();
                    
                    if (pred && node_to_delete->isRThreaded()) {
                        pred->setRight(succ);
                        pred->setRThread(true);
                    }
                } else {
                    new_child = node_to_delete->getRight();

                    Node* succ = find_successor(node_to_delete);
                    Node* pred = find_predecessor(node_to_delete);

                    if (succ && pred && succ->getLeft() == node_to_delete)
                        succ->setLeft(pred);
                }


                if (!parent) { root = new_child; } 
                else if (is_left_child) { parent->setLeft(new_child); } 
                else { 
                    parent->setRight(new_child);
                    parent->setRThread(false); 
                }
                delete node_to_delete;
                delete_completed = true;
            }
            // both children exist
            if (!delete_completed && node_to_delete->getLeft() && node_to_delete->getRight() && !node_to_delete->isRThreaded()) {
                Node* successor = node_to_delete->getRight();
                Node* successor_parent = node_to_delete;
                bool successor_is_right_child = true;

                while (successor->getLeft()) {
                    successor_parent = successor;
                    successor = successor->getLeft();
                    successor_is_right_child = false;
                }

                node_to_delete->setData(successor->getData());

                if (successor_is_right_child) { 
                    node_to_delete->setRight(successor->getRight());
                    node_to_delete->setRThread(successor->isRThreaded());
                } else { 
                    successor_parent->setLeft(successor->getRight());
                }

                delete successor;
                delete_completed = true;
            }
        }
        return true;
    }

    void inorder_traversal() const {
        if (!root) {
            cout << "Tree is empty." << endl;
            return;
        }

        Node* current = root;
        while (current && current->getLeft()) {
            current = current->getLeft();
        }

        cout << "\nIn-Order Traversal :" << endl;
 
        while (current) {
            cout << current->getData() << " ";

            if (current->isRThreaded()) {
                current = current->getRight();
            } else {
                current = find_successor(current); 
            }
        }
    }

    void destroyTree(Node* node) {
        if (!node) return;
        Node* current = node;
        Node* next_node = nullptr;
        
        while (current) {
            while (current && current->getLeft()) {
                current = current->getLeft();
            }

            while (current) {
                next_node = current->getRight(); 
                delete current;
                current = next_node;
            }
        }
        root = nullptr;
    }
};

int getValidIntInput(const string& prompt) {
    int value = 0;
    bool input_valid = false;

    while (!input_valid) {
        cout << prompt;
        string line;
        if (getline(cin, line)) {
            stringstream ss(line);
            
            if ((ss >> value) && (ss.peek() == EOF || ss.peek() == '\n' || ss.peek() == ' ' || ss.peek() == '\t')) {
                char check_char;
                if (!(ss >> check_char)) {
                    input_valid = true; 
                }
            }
        }

        if (!input_valid) {
            cout << "Invalid input. Please enter a valid integer (e.g., 123) without any extra characters." << endl;
        }
    }
    return value;
}

int main() {
    ThreadedBT tree;
    int choice;
    int key, new_key;

    bool running = true;
    while (running) {
        cout << "\n------------------Threaded Binary Tree------------------\n";
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Update" << endl;
        cout << "4. Delete" << endl;
        cout << "5. In-Order Traversal" << endl;
        cout << "6. Exit" << endl;

        choice = getValidIntInput("Enter your choice (1-6): ");

        if (choice == 1) {
            key = getValidIntInput("Enter key to insert: ");
            if (tree.insert(key)) {
                cout << "Key " << key << " inserted successfully." << endl;
            } else {
                cout << "Key " << key << " already exists." << endl;
            }
        } else if (choice == 2) {
            key = getValidIntInput("Enter key to search: ");
            if (tree.search(key)) {
                cout << "Key " << key << " found in the tree." << endl;
            } else {
                cout << "Key " << key << " not found." << endl;
            }
        } else if (choice == 3) {
            key = getValidIntInput("Enter OLD key to update: ");
            new_key = getValidIntInput("Enter NEW key: ");
            if (tree.update(key, new_key)) {
                cout << "Key " << key << " updated to " << new_key << " successfully." << endl;
            } else {
                cout << "Update failed." << endl;
            }
        } else if (choice == 4) {
            key = getValidIntInput("Enter key to delete: ");
            if (tree.remove(key)) {
                cout << "Key " << key << " deleted successfully." << endl;
            } else {
                cout << "Key " << key << " not found." << endl;
            }
        } else if (choice == 5) {
            tree.inorder_traversal();
        } else if (choice == 6) {
            cout << "Exiting the program. Goodbye!" << endl;
            running = false;
        } else {
            cout << "Please enter a valid menu option (1-6)." << endl;
        }
        
    }

    return 0;
}