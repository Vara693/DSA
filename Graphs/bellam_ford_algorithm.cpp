#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class graph {
private:
    int V;
    vector<vector<int>> edges;

public:
    graph(int v) {
        this->V = v;
    }

    void addEdge(int u, int v, int wt) {
        edges.push_back({u, v, wt});
    }

    vector<int> bellman_ford(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i=0; i<V-1; i++) {
            for (auto &it: edges) {
                int u = it[0];
                int v = it[1];
                int wt = it[2];

                if (dist[u] != INT_MAX && dist[u]+wt< dist[v]) {
                    dist[v] = dist[u]+wt;
                }
            }
        }

        //to detect -ve cycles
        for (auto &it: edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            if (dist[u] != INT_MAX && dist[u]+wt< dist[v]) {
                return {-1};
            }
        }

        return dist;
    }
};

int main() {
    graph g(6);
    g.addEdge(3, 2, 6);
    g.addEdge(5, 3, 1);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 5, -3);
    g.addEdge(1, 2, -2);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, -2);

    vector<int> dist = g.bellman_ford(0);
    for (int val: dist) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}