#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// Function to simulate work
void printNumbers(int id) {
    for (int i = 1; i <= 5; i++) {
        cout << "Thread " << id << " prints: " << i << endl;
    }
}

int main() {
    // Create a vector to hold threads
    vector<thread> threads;

    // Launch 3 threads
    for (int i = 1; i <= 3; i++) {
        threads.push_back(thread(printNumbers, i));
    }

    // Join all threads (wait for them to finish)
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    cout << "All threads finished execution!" << endl;
    return 0;
}