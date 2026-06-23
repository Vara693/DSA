#include <iostream>
#include <queue>
using namespace std;

void reverseQueue(queue<int> &q) {
    if (q.empty()) return;

    int val = q.front();
    q.pop();

    reverseQueue(q);
    q.push(val);
}
int main() {
    queue<int> q;
    q.push(200);
    q.push(-3);
    q.push(9);
    q.push(-12);
    q.push(30);
    q.push(89);
    q.push(-100);
    q.push(478);
    reverseQueue(q);
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}