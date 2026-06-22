#include <iostream>
#include <list>
#include <queue>
using namespace std;

//undirected graph
class graph {
    int V;
    list<int> *edges;

    public:
    graph(int V) {
        this->V = V;
        edges = new list<int> [V];
    }

    void addedges(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void print_graph() {
        for (int i=0; i<V; i++) {
            cout << i << " : ";
            bool first = true;
            for(int val: edges[i]) {
                if (!first) cout << ", ";
                cout << val;
                first = false;
            }
            cout << endl;
        }
    }

    void BFS(int u) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(u);
        visited[u] = true;

        while (!q.empty()) {
            int val = q.front();
            cout << val << " ";
            q.pop();
            for(int i: edges[val]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    void DFS(int u, vector<bool> &vis) {
        cout << u << " ";
        vis[u] = true;
        for (int i : edges[u]){
            if(!vis[i]) {
                DFS(i, vis);
            }
        }
    }

    bool detectCycleDFS(int srcNode, int prevNode, vector<bool> &visited) {
        visited[srcNode] = true;
        for (int val: edges[srcNode]) {
            if (!visited[val]) {
                if (detectCycleDFS(val, srcNode, visited)) { 
                    return true;
                }
            } else if (prevNode != val) {
                return true;
            } 
        }

        return false;
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (detectCycleDFS(i, -1, visited)) {
                    return true;
                }
            }
        }
        return false;
    }



    bool detectCycleBFS(int u) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;
        visited[u] = true;
        q.push(u);

        while (!q.empty()) {
            int val = q.front();
            q.pop();

            for (int num: edges[val]) {
                if (!visited[num]) {
                    visited[num] = true;
                    parent[num] = val;
                    q.push(num);
                } else if (parent[val] != num){
                    return true;
                }
            }
        }

        return false;
    }
};
int main() {
    graph gp(6);
    vector<bool> vis(6, false);
    gp.addedges(0,1);
    gp.addedges(1,5);
    gp.addedges(1,2);
    gp.addedges(1,3);
    gp.addedges(2,3);
    gp.addedges(2,4);
    gp.addedges(2,0);


   
    

    gp.print_graph();
    cout << endl;
    gp.BFS(0);
    gp.DFS(0, vis);
    cout <<endl;
    for (bool i: vis) {
        cout << i << " ";
    }
    cout << endl;

    cout << gp.hasCycle() << endl;
    
    cout << gp.detectCycleBFS(0);

    return 0;
}