#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    graph(int v) {
        this->V = v;
        adj.resize(v);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dijktraTraverval(int src) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //min-heap
        vector<int> shortestDistances(V, INT_MAX);
        shortestDistances[src] = 0;
        pq.push({shortestDistances[src], src});

        while (!pq.empty()) {
            int node = pq.top().second;
            int currDist = pq.top().first;
            pq.pop();

            // shortestDistances[node] = min(shortestDistances[node], currDist);
            for (auto it: adj[node]) {
                int nextNode = it.first;
                int dist = it.second;

                if (shortestDistances[nextNode] > currDist+dist) {
                    pq.push({currDist+dist, nextNode});
                    shortestDistances[nextNode] = currDist+dist;
                }
            }
        }

        return shortestDistances;
    }
};

int main() {
    graph g(6);
    g.addEdge(0,1,4);
    g.addEdge(0,2,4);
    g.addEdge(1,2,2);
    g.addEdge(2,3,3);
    g.addEdge(2,5,6);
    g.addEdge(2,4,1);
    g.addEdge(3,5,2);
    g.addEdge(4,5,3);

    vector<int> dist = g.dijktraTraverval(0);
    for (int val: dist) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}