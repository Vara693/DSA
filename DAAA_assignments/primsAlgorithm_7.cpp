#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class graph {
private:
    int V;
    vector<vector<int>> adj;
    const int INF = 1e9;

public:
    graph(int v) {
        this->V = v;
        adj.assign(v, vector<int>(v, INF));
    }

    void addEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // Algorithm PrimMST(adj, V, src, wt):
    // key[0..V-1] ← ∞
    // parent[0..V-1] ← -1
    // vis[0..V-1] ← false
    // key[src] ← wt
    // pq ← min-heap
    // insert (wt, src) into pq

    // while pq not empty:
    //     (currWt, node) ← extract-min from pq
    //     if vis[node] = true: continue
    //     vis[node] ← true

    //     for i ← 0 to V-1:
    //         if adj[node][i] ≠ INF and vis[i] = false and adj[node][i] < key[i]:
    //             key[i] ← adj[node][i]
    //             parent[i] ← node
    //             insert (key[i], i) into pq

    // mst ← empty list
    // sum ← 0
    // for i ← 0 to V-1:
    //     if parent[i] ≠ -1:
    //         add (parent[i], i) to mst
    //         sum ← sum + adj[parent[i]][i]
    // add {sum} to mst
    // return mst

    //time complexity = O((V^2)logV) or O((V+E)logV) depending on the graph representation
    //space complexity = O(V^2)

    vector<vector<int>> primsAlgorithm(int src, int wt) {
        vector<int> key(V, INF);
        vector<int> parent(V, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater <pair<int, int>>> pq;
        vector<bool> vis(V, false);
        key[src] = wt;
        pq.push({wt, src});

        while (!pq.empty()) {
            int node = pq.top().second;
            pq.pop();

            if (vis[node]) continue;
            vis[node] = true;

            for (int i = 0; i < V; i++) {
                if (!vis[i] && adj[node][i] != INF && adj[node][i] < key[i]) {
                    key[i] = adj[node][i];
                    parent[i] = node;
                    pq.push({key[i], i});
                }
            }
        }

        vector<vector<int>> mst;
        int sum = 0;
        for (int i = 0; i < V; i++) {
            if (parent[i] != -1) {
                mst.push_back({parent[i], i});
                sum += adj[parent[i]][i];
            }
        }
        mst.push_back({sum});
        return mst;
    }
};
int main() {
    graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 4, 2);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 1);
    vector<vector<int>> mst = g.primsAlgorithm(0, 0);
    
    for (auto &it: mst) {
        for (int val: it) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}