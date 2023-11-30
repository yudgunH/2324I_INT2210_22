#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void DFS(int v, vector<bool> &visited) const {
        visited[v] = true;
        for (int i : adj[v])
            if (!visited[i])
                DFS(i, visited);
    }

    bool isHamiltonianCycleUtil(vector<int>& path, int pos) {
        if (pos == V) {
            return (find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), path[0]) != adj[path[pos - 1]].end());
        }
        for (int v = 1; v < V; v++) {
            if (isSafe(v, path, pos)) {
                path[pos] = v;
                if (isHamiltonianCycleUtil(path, pos + 1))
                    return true;
                path[pos] = -1;
            }
        }
        return false;
    }

    bool isSafe(int v, vector<int>& path, int pos) const {
        if (find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), v) == adj[path[pos - 1]].end())
            return false;
        for (int i = 0; i < pos; i++)
            if (path[i] == v)
                return false;
        return true;
    }

public:
    Graph(int V) : V(V) {
        adj = new list<int>[V];
    }

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    bool isConnected() const {
        vector<bool> visited(V, false);
        int i;
        for (i = 0; i < V; i++)
            if (!adj[i].empty())
                break;
        if (i == V) return true;

        DFS(i, visited);
        for (i = 0; i < V; i++)
            if (!visited[i] && !adj[i].empty())
                return false;

        return true;
    }

    bool isEulerianCycle() const {
        if (!isConnected()) return false;
        for (int i = 0; i < V; i++)
            if (adj[i].size() % 2 != 0)
                return false;
        return true;
    }

    bool isHamiltonianCycle() {
        vector<int> path(V, -1);
        path[0] = 0;
        return isHamiltonianCycleUtil(path, 1);
    }
};

int main() {
    int n;
    cout << "Nhập số lượng đồ thị: ";
    cin >> n;
    vector<bool> eulerianResults(n), hamiltonianResults(n);

    for (int i = 0; i < n; ++i) {
        int V, E;
        cout << "Nhập số đỉnh và số cạnh của đồ thị " << i + 1 << ": ";
        cin >> V >> E;
        Graph g(V);
        cout << "Nhập các cạnh (dạng u v): " << endl;
        for (int j = 0; j < E; ++j) {
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v);
        }
        eulerianResults[i] = g.isEulerianCycle();
        hamiltonianResults[i] = g.isHamiltonianCycle();
    }

    cout << "Kết quả kiểm tra chu trình Euler và Hamilton cho " << n << " đồ thị:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Đồ thị " << i + 1 << ":" << endl;
        cout << "  - Chu trình Euler: " << (eulerianResults[i] ? "Có" : "Không") << endl;
        cout << "  - Chu trình Hamilton: " << (hamiltonianResults[i] ? "Có" : "Không") << endl;
    }

    return 0;
}
