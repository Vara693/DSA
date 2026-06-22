#include <iostream>
using namespace std;

#define SIZE 10

class HashLinear {
    int table[SIZE];

public:
    HashLinear() {
        for (int i = 0; i < SIZE; i++)
            table[i] = -1;
    }

    void insert(int key) {
        int index = key % SIZE;

        // Linear probing
        int i = 0;
        while (table[(index + i) % SIZE] != -1) {
            i++;
            if (i == SIZE) {
                cout << "Hash Table Full!" << endl;
                return;
            }
        }

        table[(index + i) % SIZE] = key;
    }

    void display() {
        cout << "\nHash Table (Linear Probing):\n";
        for (int i = 0; i < SIZE; i++)
            cout << i << " --> " << table[i] << endl;
    }
};

class HashQuadratic {
    int table[SIZE];

public:
    HashQuadratic() {
        for (int i = 0; i < SIZE; i++)
            table[i] = -1;
    }

    void insert(int key) {
        int index = key % SIZE;

        int i = 0;
        while (table[(index + i*i) % SIZE] != -1) {
            i++;
            if (i == SIZE) {
                cout << "Hash Table Full!" << endl;
                return;
            }
        }

        table[(index + i*i) % SIZE] = key;
    }

    void display() {
        cout << "\nHash Table (Quadratic Probing):\n";
        for (int i = 0; i < SIZE; i++)
            cout << i << " --> " << table[i] << endl;
    }
};

#include <list>

class HashChaining {
    list<int> table[SIZE];

public:
    void insert(int key) {
        int index = key % SIZE;
        table[index].push_back(key);
    }

    void display() {
        cout << "\nHash Table (Chaining):\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " --> ";
            for (int x : table[i])
                cout << x << " -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    int keys[] = {12, 22, 32, 42, 52, 15, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    HashLinear HL;
    HashQuadratic HQ;
    HashChaining HC;

    for (int i = 0; i < n; i++) {
        HL.insert(keys[i]);
        HQ.insert(keys[i]);
        HC.insert(keys[i]);
    }

    HL.display();
    HQ.display();
    HC.display();

    return 0;
}
