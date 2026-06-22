#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Graph {
private:
    int V;
    list<int> *l;

public:
    Graph(int v) {
        this->V = v;
        l = new list<int> [v];
    }

    void addEdge(int u, int v) {
        l[u].push_back(v);
    }

    //detect cycle using DFS
    bool hasCycle(int val, vector<bool> &visited, vector<bool> &rPath) { //O(V+E)
        visited[val] = true;
        rPath[val] = true;

        for (int num: l[val]) {
            if (!visited[num]) {
                if (hasCycle(num, visited, rPath)) return true;
            } else if (rPath[num]) return true;
        }
        rPath[val] = false;
        return false;
    }


    bool isCycle() {
        vector<bool> visited(V, false);
        vector<bool> rPath(V, false);
        for (int i=0; i<V; i++) {
            if (!visited[i]) {
                if (hasCycle(i, visited, rPath)) {
                    return true;
                }
            }
        }
        return false;
    }

    //topological sorting usinf dfs
    void topologicalSort(int curr, vector<bool> &vis, stack<int> &st) {
        vis[curr] = true;
        for (int num: l[curr]) {
            if (!vis[num]) {
                topologicalSort(num, vis, st);
            }
        }
        st.push(curr);
    }

    void helper(stack<int> &st) {
        vector<bool> vis(V, false);
        for (int i=0; i<V; i++) {
            if (!vis[i]) {
                topologicalSort(i, vis, st);
            }
        }
    }

    //toplogical sorting using bfs(Kahn's algorithm)
    vector<int> toplogicalSortBfs() {
        queue<int> q;
        // vector<bool> vis(V, false); not needed cause of kahn's algo
        vector<int> indegree(V, 0);
        vector<int> ans;

        //step 1
        for (int i=0; i<V; i++) {
            for (int val: l[i]) {
                indegree[val]++;
            }
        }

        //step 2
        for (int i=0; i<V; i++) {
            if (indegree[i]==0) {
                q.push(i);
            }
        }

        //step 3
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            ans.push_back(curr);
            // vis[curr] = true;
            for (int val: l[curr]) {
                indegree[val]--;
                if (indegree[val] == 0) {
                    q.push(val);
                }
            }
        }
        return ans;
    }

};
int main() {
    // Graph gp(4);
    // gp.addEdge(1,0);
    // gp.addEdge(0,2);
    // gp.addEdge(2,3);
    // gp.addEdge(3,0);
    // gp.addEdge(2,1);

    // cout << gp.isCycle() << endl;

    // stack<int> st;
    Graph g(6);
    g.addEdge(5,0);
    g.addEdge(4,0);
    g.addEdge(5,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.addEdge(4,1);

    // g.helper(st);
    // while (!st.empty()) {
    //     cout << st.top() << " ";
    //     st.pop();
    // }

    vector<int> result = g.toplogicalSortBfs();
    for (int num: result) {
        cout << num << " ";
    }

    cout << endl;

    return 0;
}