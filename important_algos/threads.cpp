#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <thread>
using namespace std;

void threading(int id) {
    cout << "thread " << id << endl; 
}
int main() {
    thread t(threading, 1);

    t.join();
    return 0;
}