#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V;    
    list<int> *adj;    

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFS(*i, visited);
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        int i;
        for (i = 0; i < V; i++)
            if (adj[i].size() > 0)
                break;

        if (i == V)
            return true;

        DFS(i, visited);

        for (i = 0; i < V; i++)
            if (visited[i] == false && adj[i].size() > 0)
                return false;

        return true;
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    bool isEulerianCycle() {
        if (!isConnected())
            return false;

        vector<int> in(V, 0), out(V, 0);

        for (int i = 0; i < V; i++) {
            for (auto j : adj[i]) {
                out[i]++;
                in[j]++;
            }
        }

        for (int i = 0; i < V; i++)
            if (in[i] != out[i])
                return false;

        return true;
    }
};

int main() {
    int V, E;
    cout << "Nhập số lượng đỉnh (V): ";
    cin >> V;

    Graph g(V);

    cout << "Nhập số lượng cạnh (E): ";
    cin >> E;

    cout << "Nhập cạnh (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    if (g.isEulerianCycle())
        cout << "Đồ thị có chu trình Euler." << endl;
    else
        cout << "Đồ thị không có chu trình Euler." << endl;

    return 0;
}
