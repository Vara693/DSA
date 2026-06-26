#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

// ---------------------------
// Strong integer input validator
// ---------------------------
bool parseIntStrict(const string &s, int &out) {
    if (s.empty()) return false;
    string trimmed;
    for (char ch : s) {
        if (!isspace(static_cast<unsigned char>(ch))) trimmed += ch;
    }

    if (trimmed.empty()) return false;

    int start = 0;
    if (trimmed[0] == '-' || trimmed[0] == '+') start = 1;

    if (start == static_cast<int>(trimmed.size())) return false; // only sign

    for (size_t i = start; i < trimmed.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(trimmed[i]))) return false;
    }

    try {
        size_t idx;
        long val = stol(trimmed, &idx);
        if (idx != trimmed.size()) return false;
        if (val > numeric_limits<int>::max() || val < numeric_limits<int>::min())
            return false;
        out = static_cast<int>(val);
        return true;
    } catch (...) {
        return false;
    }
}

// Safe integer input
int readInt(const string &prompt) {
    string line;
    int val;
    bool valid = false;
    while (!valid) {
        cout << prompt;
        getline(cin, line);
        valid = parseIntStrict(line, val);
        if (!valid)
            cout << "Invalid input. Please enter a valid integer.\n";
    }
    return val;
}

class HashSet {
private:
    vector<vector<int>> table;
    int capacity;
    int currentSize;

    int hash(int key) const {
        return static_cast<int>(key >= 0 ? key : -key) % capacity;
    }

    bool containsInBucket(const vector<int> &bucket, int key) const {
        for (int i = 0; i < bucket.size(); ++i)
            if (bucket[i] == key)
                return true;
        return false;
    }

public:
    explicit HashSet(int cap = 10) : capacity(cap), currentSize(0) {
        table.resize(capacity);
    }

    // ---------------------------
    // Create / Insert
    // ---------------------------
    bool insert(int key) {
        size_t idx = hash(key);
        if (containsInBucket(table[idx], key))
            return false; // already exists
        table[idx].push_back(key);
        currentSize++;
        return true;
    }

    // ---------------------------
    // Read / Search
    // ---------------------------
    bool contains(int key) const {
        size_t idx = hash(key);
        return containsInBucket(table[idx], key);
    }

    // ---------------------------
    // Delete / Remove
    // ---------------------------
    bool remove(int key) {
        size_t idx = hash(key);
        vector<int> &bucket = table[idx];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i] == key) {
                // shift manually instead of erase() (to avoid break)
                for (size_t j = i + 1; j < bucket.size(); ++j)
                    bucket[j - 1] = bucket[j];
                bucket.pop_back();
                currentSize--;
                return true;
            }
        }
        return false;
    }

    // ---------------------------
    // Update (remove + insert new key)
    // ---------------------------
    bool update(int oldKey, int newKey) {
        if (!contains(oldKey)) return false;
        if (contains(newKey)) return false;
        remove(oldKey);
        insert(newKey);
        return true;
    }

    // ---------------------------
    // Utility / Display
    // ---------------------------
    size_t size() const { return currentSize; }

    vector<int> getAllElements() const {
        vector<int> elements;
        for (size_t i = 0; i < capacity; ++i)
            for (size_t j = 0; j < table[i].size(); ++j)
                elements.push_back(table[i][j]);
        return elements;
    }
};

// ---------------------------
// Display Helpers
// ---------------------------
void displaySet(const HashSet &hs) {
    vector<int> elems = hs.getAllElements();
    cout << "Current elements in HashSet: ";
    if (elems.empty()) {
        cout << "(empty)\n";
        return;
    }
    for (size_t i = 0; i < elems.size(); ++i)
        cout << elems[i] << (i + 1 < elems.size() ? ", " : "\n");
}

// ---------------------------
// Main Menu
// ---------------------------
int main() {
    HashSet hs(10);
    bool running = true;

    while (running) {
        cout << "\n====== HashSet Operations ======\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Update\n";
        cout << "5. Display\n";
        cout << "6. Size\n";
        cout << "0. Exit\n";

        int choice = readInt("Enter your choice: ");
        if (choice == 0) {
            running = false;
        } else if (choice == 1) {
            int key = readInt("Enter integer to insert: ");
            bool inserted = hs.insert(key);
            cout << (inserted ? "Inserted successfully.\n" : "Element already exists.\n");
        } else if (choice == 2) {
            int key = readInt("Enter integer to search: ");
            bool found = hs.contains(key);
            cout << (found ? "Element found.\n" : "Element not found.\n");
        } else if (choice == 3) {
            int key = readInt("Enter integer to delete: ");
            bool removed = hs.remove(key);
            cout << (removed ? "Deleted successfully.\n" : "Element not found.\n");
        } else if (choice == 4) {
            int oldKey = readInt("Enter element to update: ");
            int newKey = readInt("Enter new value: ");
            bool updated = hs.update(oldKey, newKey);
            cout << (updated ? "Updated successfully.\n" : "Update failed (element missing or duplicate).\n");
        } else if (choice == 5) {
            displaySet(hs);
        } else if (choice == 6) {
            cout << "Current size: " << hs.size() << "\n";
        } else {
            cout << "Invalid option.\n";
        }
    }

    cout << "Exiting program.\n";
    return 0;
}
