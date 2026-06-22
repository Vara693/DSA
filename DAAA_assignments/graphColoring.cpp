// 1. Define graph using adjacency matrix graph[V][V]

// 2. Create color[] array of size V and initialize with 0

// 3. Define isSafe(node, col):
//       for all vertices k:
//           if graph[node][k] == 1 AND color[k] == col
//               return false
//       return true

// 4. Define recursive function solve(node):

// 5. If node == V:
//       print color assignment
//       return true

// 6. For col from 1 to m:
//       if isSafe(node, col):
//           assign color[node] = col
//           if solve(node+1) == true:
//               return true
//           else backtrack → color[node] = 0

// 7. If no color works → return false

// 8. Call solve(0)

// 9. If solution exists → print colors
//    else → print "No solution"



#include <iostream>
using namespace std;

#define V 4

int graph[V][V] = {
    {0,1,1,1},
    {1,0,1,0},
    {1,1,0,1},
    {1,0,1,0}
};

int m = 3; // number of colors
int color[V];

// Check if safe
bool isSafe(int node, int c) {
    for(int k = 0; k < V; k++) {
        if(graph[node][k] == 1 && color[k] == c)
            return false;
    }
    return true;
}

// Backtracking function
bool solve(int node) {

    if(node == V) {
        cout << "Color Assignment:\n";
        for(int i = 0; i < V; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
        return true;
    }

    for(int c = 1; c <= m; c++) {

        if(isSafe(node, c)) {

            color[node] = c; // assign color

            if(solve(node + 1))
                return true;

            color[node] = 0; // backtrack
        }
    }

    return false;
}

int main() {

   
    for(int i = 0; i < V; i++)
        color[i] = 0;

    if(!solve(0))
        cout << "No solution exists";

    return 0;
}


// Time Complexity = O(V*m^V)
// Space Complexity = O(V^2)