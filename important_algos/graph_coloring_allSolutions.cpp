#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    graph(int v) {
        this->V = v;
        adj.resize(v);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool isSafe(int node, char color, vector<char> &colorsAssigned) {
        for (auto it: adj[node]) {
            if (color == colorsAssigned[it]) return false;
        }

        return true;
    }

    void graphColoring(int node, vector<char> &colorAssigned, string &colors) {
        if (node>=V) {
            for (char ch: colorAssigned) {
                cout << ch << " ";
            }

            cout << endl;
            return;
        }

        for  (int i=0; i<colors.size(); i++) {
            if (isSafe(node, colors[i], colorAssigned)) {
                colorAssigned[node] = colors[i];
                graphColoring(node+1, colorAssigned, colors);
                colorAssigned[node] = '\0';
            }
        }
    }
};
int main() {
    graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(0,3);
    string colors = "RGB";
    vector<char> colorsAssigned(4, '\0');
    g.graphColoring(0, colorsAssigned, colors);
    return 0;
}