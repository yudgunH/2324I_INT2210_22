#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
    int V; 
    list<int> *adj; 
    void DFSUtil(int v, vector<bool>& visited, vector<int>& discovery, 
                 vector<int>& low, vector<int>& parent, bool& isArticulation) {
        static int time = 0;
        int children = 0; 
        visited[v] = true;
        discovery[v] = low[v] = ++time;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            int u = *i;
            if (!visited[u]) {
                children++;
                parent[u] = v;
                DFSUtil(u, visited, discovery, low, parent, isArticulation);

                low[v] = min(low[v], low[u]);
                if (parent[v] == -1 && children > 1)
                    isArticulation = true;
                if (parent[v] != -1 && low[u] >= discovery[v])
                    isArticulation = true;
            } else if (u != parent[v]) {
                low[v] = min(low[v], discovery[u]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int v, int w) {
        adj[v].push_back(w); 
        adj[w].push_back(v); 
    }

    bool isBiconnected() {
        vector<bool> visited(V, false);
        vector<int> discovery(V, -1), low(V, -1), parent(V, -1);
        bool isArticulation = false;

        DFSUtil(0, visited, discovery, low, parent, isArticulation);

        for (int i = 0; i < V; i++) {
            if (visited[i] == false)
                return false;
        }

        return !isArticulation;
    }
};

int main() {
    int V, E;
    cout << "Nhập số lượng đỉnh (V): ";
    cin >> V;

    Graph g(V);

    cout << "Nhập số lượng cạnh (E): ";
    cin >> E;

    cout << "Nhập các cạnh (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    if (g.isBiconnected()) {
        cout << "Đồ thị là biconnected." << endl;
    } else {
        cout << "Đồ thị không phải là biconnected." << endl;
    }

    return 0;
}
