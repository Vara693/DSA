#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void prims(vector<vector<int>> &graph, int V) {
    vector<int> key(V, INT_MAX);     // Minimum edge weight
    vector<bool> mst(V, false);      // Included in MST or not
    vector<int> parent(V, -1);       // Store MST

    key[0] = 0; // Start from vertex 0

    for (int count = 0; count < V - 1; count++) {

        // Find minimum key vertex not in MST
        int u = -1;
        int mini = INT_MAX;

        for (int i = 0; i < V; i++) {
            if (!mst[i] && key[i] < mini) {
                mini = key[i];
                u = i;
            }
        }

        mst[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < V; v++) {

            // graph[u][v] != 0 means edge exists
            if (graph[u][v] != 0 &&
                !mst[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print MST
    int totalCost = 0;

    cout << "Edge \tWeight\n";

    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i
             << "\t" << graph[parent[i]][i] << endl;

        totalCost += graph[parent[i]][i];
    }

    cout << "Total Cost = " << totalCost << endl;
}

int main() {

    int V = 5;

    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    prims(graph, V);

    return 0;
}