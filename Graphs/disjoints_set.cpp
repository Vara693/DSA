#include <iostream>
#include <vector>
using namespace std;

class disjointSet{
private:
    int V;
    vector<int> parent;
    vector<int> size;
    
public:
    // T.C = O(4*alpha) ~ O(1)
    //S.C = O(n)
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
int main() {
    disjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(5, 6);
    ds.unionBySize(6, 7);
    if (ds.findParent(3) == ds.findParent(7)) {
        cout << "Same";
    } else {
        cout << "Not Same";
    }
    cout << endl;

    ds.unionBySize(3, 7);
    if (ds.findParent(3) == ds.findParent(7)) {
        cout << "Same";
    } else {
        cout << "Not Same";
    }
    cout << endl;
    return 0;
}