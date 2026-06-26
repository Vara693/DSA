#include <stdio.h>
#include <stdlib.h>

// Node structure for Right Threaded Binary Tree
struct Node {
    int data;
    struct Node *left, *right;
    int rthread;  // 1 = thread, 0 = right child
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->rthread = 1;  // new node will have right thread initially
    return node;
}

// Insert a node into Right Threaded Binary Tree
struct Node* insert(struct Node* root, int key) {
    struct Node* ptr = root;
    struct Node* parent = NULL;

    while (ptr != NULL) {
        if (key == ptr->data) {
            printf("Duplicate key %d not allowed.\n", key);
            return root;
        }

        parent = ptr;

        if (key < ptr->data) {
            ptr = ptr->left;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    struct Node* temp = createNode(key);

    // If tree is empty
    if (parent == NULL) {
        root = temp;
    }
    // Insert as left child
    else if (key < parent->data) {
        temp->left = parent->left;
        temp->right = parent;
        parent->left = temp;
    }
    // Insert as right child
    else {
        temp->right = parent->right;
        parent->rthread = 0;
        parent->right = temp;
    }

    printf("Node %d inserted successfully.\n", key);
    return root;
}

// Function to find the leftmost node
struct Node* leftMost(struct Node* n) {
    if (n == NULL)
        return NULL;

    while (n->left != NULL)
        n = n->left;

    return n;
}

// Inorder traversal using right threads
void inorder(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Node* cur = leftMost(root);
    while (cur != NULL) {
        printf("%d ", cur->data);

        // If right thread exists
        if (cur->rthread)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
    }
    printf("\n");
}

// Search node in RTBT
struct Node* search(struct Node* root, int key) {
    struct Node* ptr = root;

    while (ptr != NULL) {
        if (key == ptr->data)
            return ptr;
        else if (key < ptr->data)
            ptr = ptr->left;
        else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }
    return NULL;
}

struct Node* inorderSuccessor(struct Node* node) {
    if (node->rthread)
        return node->right; 

    node = node->right;
    while (node->left != NULL)
        node = node->left; 

    return node;
}


struct Node* deleteNode(struct Node* root, int key) {
    struct Node *parent = NULL, *curr = root;
    int found = 0;

    while (curr != NULL) {
        if (key == curr->data) {
            found = 1;
            break;
        }
        parent = curr;
        if (key < curr->data)
            curr = curr->left;
        else if (curr->rthread == 0)
            curr = curr->right;
        else
            break;
    }

    if (!found) {
        printf("Key %d not found.\n", key);
        return root;
    }

    if (curr->left != NULL && curr->rthread == 0) {
        struct Node* succ = inorderSuccessor(curr);
        curr->data = succ->data;
        key = succ->data;
        parent = curr;
        curr = curr->right;
        while (curr->left != NULL)
            curr = curr->left;
    }

    struct Node* child;
    if (curr->left == NULL)
        child = curr->rthread ? NULL : curr->right;
    else
        child = curr->left;

    if (parent == NULL)
        root = child;
    else if (key < parent->data)
        parent->left = child;
    else if (parent->rthread == 0)
        parent->right = child;
    else
        parent->rthread = 1;

    struct Node* pred = NULL;
    struct Node* succ = NULL;

    if (curr->left != NULL) {
        pred = curr->left;
        while (pred->rthread == 0)
            pred = pred->right;
    } else if (parent && key < parent->data) {
        pred = parent;
    }

    if (curr->rthread)
        succ = curr->right;
    else {
        succ = curr->right;
        if (succ != NULL)
            while (succ->left != NULL)
                succ = succ->left;
    }

    if (pred != NULL && pred->rthread)
        pred->right = succ;

    free(curr);
    printf("Node %d deleted successfully.\n", key);
    return root;
}

// Update operation (delete old value, insert new one)
struct Node* update(struct Node* root, int oldVal, int newVal) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return root;
    }

    if (search(root, newVal) != NULL) {
        printf("Value %d already exists. Cannot update.\n", newVal);
        return root;
    }

    root = deleteNode(root, oldVal);
    root = insert(root, newVal);

    printf("Node value updated from %d to %d successfully.\n", oldVal, newVal);
    return root;
}

// Function for safe integer input
int get_integer_input() {
    int value;
    char term;
    while (1) {
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            printf("Invalid input. Please enter a valid whole number: ");
            while (getchar() != '\n');
        } else {
            return value;
        }
    }
}

// Main menu
int main() {
    struct Node* root = NULL;
    int choice, val, oldVal, newVal;

    while (1) {
        printf("\n--- Right Threaded Binary Tree (CRUD) ---\n");
        printf("1. Insert\n2. Display (Inorder)\n3. Search\n4. Update\n5. Delete\n6. Exit\n");
        printf("Enter your choice: ");
        choice = get_integer_input();

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                val = get_integer_input();
                root = insert(root, val);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorder(root);
                break;
            case 3:
                printf("Enter value to search: ");
                val = get_integer_input();
                if (search(root, val))
                    printf("Node %d found.\n", val);
                else
                    printf("Node %d not found.\n", val);
                break;
            case 4:
                printf("Enter old value: ");
                oldVal = get_integer_input();
                printf("Enter new value: ");
                newVal = get_integer_input();
                root = update(root, oldVal, newVal);
                break;
            case 5:
                printf("Enter value to delete: ");
                val = get_integer_input();
                root = deleteNode(root, val);
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}