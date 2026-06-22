#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class disjointSet{
private:
    int V;
    vector<int> parent;
    vector<int> size;
    
public:
    disjointSet(int v) {
        this->V = v;
        parent.resize(V+1);
        size.resize(V+1, 1);
        for (int i=0; i<=V; i++) {
            parent[i] = i;
        }
    }

    //finding the ultimate parent
    int findParent(int u) {
        if (parent[u] == u) {
            return u;
        }

        return parent[u] = findParent(parent[u]);
    }

    //union by size
    void unionBySize(int u, int v) {
        int ul_u = findParent(u);
        int ul_v = findParent(v);

        if (ul_u == ul_v) {
            return;
        }

        if (size[ul_u] < size[ul_v]) {
            parent[ul_u] = ul_v;
            size[ul_v] += size[ul_u];
        } else {
            parent[ul_v] = ul_u;
            size[ul_u] += size[ul_v];
        }
    }
};

class graph {
private:
    int V;
    vector<pair<int, pair<int, int>>> edges;

public:
    graph(int v) {
        this->V = v;
    }

    void addEdge(int u, int v, int wt) {
        edges.push_back({wt, {u, v}});
    }

    //kruskal's algorithm
    vector<vector<int>> kruskalsAlgo() {
        vector<vector<int>> ans;
        disjointSet ds(V);

        //ElogE
        sort(edges.begin(), edges.end());
        int mstWt = 0;

        //E*O(1)
        for (auto &it: edges) { 
            int wt = it.first;
            int node = it.second.first;
            int nextNode = it.second.second;

            if (ds.findParent(node) != ds.findParent(nextNode)) {
                mstWt += wt;
                ds.unionBySize(node, nextNode);
                ans.push_back({node, nextNode});
            }
        }

        ans.push_back({mstWt});
        return ans;
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

    vector<vector<int>> mst = g.kruskalsAlgo();
    for (int i=0; i<mst.size(); i++) {
        for (int val: mst[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}