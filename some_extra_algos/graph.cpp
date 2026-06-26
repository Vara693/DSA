#include <iostream>
using namespace std;

struct Node {
    int vertex;
    Node* next;
};

class Graph {
private:
    int maxVertices;
    int vertexCount;
    Node** adj;

public:
    Graph(int n) {
        maxVertices = n;
        vertexCount = 0;

        adj = new Node*[maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adj[i] = 0;
        }
    }

    int findVertex(int v) {
        for (int i = 0; i < vertexCount; i++) {
            if (adj[i] != 0 && adj[i]->vertex == v) return i;
        }
        return -1;
    }

    void insertVertex(int v) {
        if (vertexCount == maxVertices) {
            cout << "Graph full. Cannot insert more vertices.\n";
            return;
        }
        if (findVertex(v) != -1) {
            cout << "Vertex already exists.\n";
            return;
        }

        adj[vertexCount] = new Node();
        adj[vertexCount]->vertex = v;
        adj[vertexCount]->next = 0;
        vertexCount++;

        cout << "Vertex inserted.\n";
    }

    void insertEdge(int u, int v) {
        int ui = findVertex(u);
        int vi = findVertex(v);

        if (ui == -1 || vi == -1) {
            cout << "One or both vertices not found.\n";
            return;
        }

        Node* temp = adj[ui];
        while (temp->next != 0) temp = temp->next;

        Node* newNode = new Node();
        newNode->vertex = v;
        newNode->next = 0;
        temp->next = newNode;

        cout << "Edge inserted.\n";
    }

    void deleteEdge(int u, int v) {
        int ui = findVertex(u);
        if (ui == -1) {
            cout << "Vertex not found.\n";
            return;
        }

        Node* temp = adj[ui];
        Node* prev = 0;

        while (temp != 0 && !(temp->vertex == v && prev != 0)) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == 0 || prev == 0) {
            cout << "Edge not found.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;

        cout << "Edge deleted.\n";
    }

    void deleteVertex(int v) {
        int idx = findVertex(v);
        if (idx == -1) {
            cout << "Vertex not found.\n";
            return;
        }

        Node* temp = adj[idx];
        while (temp != 0) {
            Node* t2 = temp;
            temp = temp->next;
            delete t2;
        }

        for (int i = idx; i < vertexCount - 1; i++) {
            adj[i] = adj[i + 1];
        }
        vertexCount--;

        for (int i = 0; i < vertexCount; i++) {
            Node* cur = adj[i];
            Node* prev = 0;

            while (cur != 0) {
                if (cur->vertex == v) {
                    if (prev == 0) {
                        Node* t = cur;
                        adj[i] = cur->next;
                        cur = cur->next;
                        delete t;
                    } else {
                        prev->next = cur->next;
                        delete cur;
                        cur = prev->next;
                    }
                } else {
                    prev = cur;
                    cur = cur->next;
                }
            }
        }

        cout << "Vertex deleted.\n";
    }

    void display() {
        if (vertexCount == 0) {
            cout << "Graph empty.\n";
            return;
        }

        for (int i = 0; i < vertexCount; i++) {
            Node* temp = adj[i];
            cout << temp->vertex << " -> ";

            temp = temp->next;
            while (temp != 0) {
                cout << temp->vertex << " ";
                temp = temp->next;
            }

            cout << "\n";
        }
    }

    void BFS(int start) {
        int si = findVertex(start);
        if (si == -1) {
            cout << "Start vertex not found.\n";
            return;
        }

        int visited[100] = {0};
        int queue[100];
        int front = 0, rear = 0;

        queue[rear] = si;
        visited[si] = 1;

        while (front <= rear) {
            int idx = queue[front];
            front++;

            cout << adj[idx]->vertex << " ";

            Node* temp = adj[idx]->next;
            while (temp != 0) {
                int vi = findVertex(temp->vertex);
                if (visited[vi] == 0) {
                    rear++;
                    queue[rear] = vi;
                    visited[vi] = 1;
                }
                temp = temp->next;
            }
        }
        cout << "\n";
    }

    void DFS(int start) {
        int si = findVertex(start);
        if (si == -1) {
            cout << "Start vertex not found.\n";
            return;
        }

        int visited[100] = {0};
        int stack[100];
        int top = -1;

        top++;
        stack[top] = si;

        while (top >= 0) {
            int idx = stack[top];
            top--;

            if (visited[idx] == 0) {
                cout << adj[idx]->vertex << " ";
                visited[idx] = 1;
            }

            Node* temp = adj[idx]->next;

            int tempStore[100];
            int c = 0;

            while (temp != 0) {
                int vi = findVertex(temp->vertex);
                if (visited[vi] == 0) {
                    tempStore[c] = vi;
                    c++;
                }
                temp = temp->next;
            }

            int i = c - 1;
            while (i >= 0) {
                top++;
                stack[top] = tempStore[i];
                i--;
            }
        }
        cout << "\n";
    }
};

int getValidatedInt() {
    string s;
    int val = 0;
    int sign = 1;
    int idx = 0;
    int valid = 0;

    while (valid == 0) {
        cout << "(an integer): ";
        getline(cin, s);

        while (idx < (int)s.size() && (s[idx] == ' ' || s[idx] == '\t')) idx++;

        if (idx < (int)s.size() && (s[idx] == '-' || s[idx] == '+')) {
            if (s[idx] == '-') sign = -1;
            idx++;
        }

        val = 0;
        int digitFound = 0;
        while (idx < (int)s.size() && s[idx] >= '0' && s[idx] <= '9') {
            digitFound = 1;
            val = val * 10 + (s[idx] - '0');
            idx++;
        }

        while (idx < (int)s.size() && (s[idx] == ' ' || s[idx] == '\t')) idx++;

        if (digitFound == 1 && idx == (int)s.size()) {
            val *= sign;
            valid = 1;
        } else {
            cout << "Invalid integer. Try again.\n";
        }
        idx = 0;
        sign = 1;
    }
    return val;
}

int main() {
    Graph g(100);
    int choice = 1;

    while (choice != 0) {
        cout << "\n---- GRAPH MENU ----\n";
        cout << "1. Insert Vertex\n";
        cout << "2. Insert Edge\n";
        cout << "3. Delete Edge\n";
        cout << "4. Delete Vertex\n";
        cout << "5. Display Graph\n";
        cout << "6. BFS\n";
        cout << "7. DFS\n";
        cout << "0. Exit\n";
        cout << "Enter choice";

        choice = getValidatedInt();

        if (choice == 1) {
            cout << "Enter vertex value";
            int v = getValidatedInt();
            g.insertVertex(v);
        }

        if (choice == 2) {
            cout << "Enter source";
            int u = getValidatedInt();
            cout << "Enter destination";
            int v = getValidatedInt();
            g.insertEdge(u, v);
        }

        if (choice == 3) {
            cout << "Enter source";
            int u = getValidatedInt();
            cout << "Enter destination";
            int v = getValidatedInt();
            g.deleteEdge(u, v);
        }

        if (choice == 4) {
            cout << "Enter vertex to delete";
            int v = getValidatedInt();
            g.deleteVertex(v);
        }

        if (choice == 5) {
            g.display();
        }

        if (choice == 6) {
            cout << "Enter start vertex";
            int v = getValidatedInt();
            g.BFS(v);
        }

        if (choice == 7) {
            cout << "Enter start vertex";
            int v = getValidatedInt();
            g.DFS(v);
        }
    }

    return 0;
}
