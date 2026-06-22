#include <iostream>
using namespace std;

struct Node {
    int coeff;
    int pow;
    Node* next;

    Node(int c, int p) {
        coeff = c;
        pow = p;
        next = NULL;
    }
};

// Insert node in descending order of power
void insert(Node*& head, int coeff, int pow) {
    Node* newNode = new Node(coeff, pow);

    if (!head || head->pow < pow) {  
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next && temp->next->pow > pow)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

// Add two polynomials
Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;

    while (p1 && p2) {
        if (p1->pow == p2->pow) {
            insert(result, p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->pow > p2->pow) {
            insert(result, p1->coeff, p1->pow);
            p1 = p1->next;
        }
        else {
            insert(result, p2->coeff, p2->pow);
            p2 = p2->next;
        }
    }

    // Add remaining terms
    while (p1) {
        insert(result, p1->coeff, p1->pow);
        p1 = p1->next;
    }
    while (p2) {
        insert(result, p2->coeff, p2->pow);
        p2 = p2->next;
    }

    return result;
}

// Display polynomial
void display(Node* head) {
    if (!head) {
        cout << "0";
        return;
    }

    while (head) {
        cout << head->coeff << "x^" << head->pow;
        if (head->next) cout << " + ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL;

    // Polynomial 1: 5x^3 + 4x^1 + 2
    insert(poly1, 5, 3);
    insert(poly1, 4, 1);
    insert(poly1, 2, 0);

    // Polynomial 2: 3x^3 + 2x^2 + 1
    insert(poly2, 3, 3);
    insert(poly2, 2, 2);
    insert(poly2, 1, 0);

    cout << "Polynomial 1: ";
    display(poly1);

    cout << "Polynomial 2: ";
    display(poly2);

    Node* result = addPoly(poly1, poly2);

    cout << "Resultant Polynomial: ";
    display(result);

    return 0;
}
