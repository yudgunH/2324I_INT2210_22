#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
    int V; 
    list<int> *adj;
    void bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                    vector<int>& low, int& bridges, int parent = -1) {
        static int time = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;
        for (int v : adj[u]) {
            if (!visited[v]) {
                bridgeUtil(v, visited, disc, low, bridges, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    bridges++;
                }
            } else if (v != parent) {
                low[u] = min(low[u], disc[v]);
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

    bool isEdgeConnected() {
        vector<bool> visited(V, false);
        vector<int> disc(V), low(V);
        int bridges = 0;
        for (int i = 0; i < V; ++i)
            if (!visited[i])
                bridgeUtil(i, visited, disc, low, bridges);
        return bridges == 0;
    }
};

int main() {
    int V, E;
    cout << "Nhập số đỉnh (V): ";
    cin >> V;
    Graph g(V);
    cout << "Nhập số cạnh (E): ";
    cin >> E;
    cout << "Nhập cạnh (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    if (g.isEdgeConnected()) {
        cout << "Đồ thị là liên thông cạnh." << endl;
    } else {
        cout << "Đồ thị không liên thông cạnh." << endl;
    }
    return 0;
}
