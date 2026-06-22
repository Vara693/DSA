#include <iostream>
#include <vector>
#include <queue>
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

    vector<vector<int>> primsAlgorithm(int src, int wt) {
        vector<bool> vis(V);
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        vector<vector<int>> mst;
        int mstWeightsSum = 0;
        pq.push({wt, {src, -1}});  //O(logE)

        while (!pq.empty()) { //O((V+E)logE)
            int currWt = pq.top().first;
            int node = pq.top().second.first;
            int parent = pq.top().second.second;
            pq.pop();

            if (vis[node]) continue;
            vis[node] = true;
            mstWeightsSum+=currWt;

            if (parent != -1) {
                mst.push_back({parent, node});
            }

            for (auto &it: adj[node]) {
                if (!vis[it.first]) {
                    pq.push({it.second, {it.first, node}});
                }
            }
        }
        mst.push_back({mstWeightsSum});
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