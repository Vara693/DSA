#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool isSafe(int v, int pos, vector<vector<int>> &graph, vector<int> &path) {
    if (graph[path[pos-1]][v] == 0) return false;

    for (int i=0; i<pos; i++) {
        if (path[i] == v) return false;
    }

    return true;
}


void hamiltonian(int pos, int V, vector<vector<int>> &graph, vector<int> &path) {
    if (pos == V) {
        if (graph[path[pos-1]][path[0]] == 1) {
            for (int val: path) {
                cout << val << "->";
            }
            cout << path[0] << endl;
        }
        return;
    }


    for (int v=1; v<V; v++) {
        if (isSafe(v, pos, graph, path)) {
            path[pos] = v;
            hamiltonian(pos+1, V, graph, path);
            path[pos] = -1;
        }
    }
}
int main() {
    int V=5;
    vector<vector<int>> graph = {{0,1,1,0,1}, {1,0,1,1,1}, {1,1,0,1,0}, {0,1,1,0,1}, {1,1,0,1,0}};
    vector<int> path(V, -1);
    path[0] = 0;
    hamiltonian(1, V, graph, path);
    return 0;
}