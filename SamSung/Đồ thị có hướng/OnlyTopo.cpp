#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                topologicalSortUtil(*i, visited, Stack);
            }
        }
        Stack.push(v);
    }

    bool isEdge(int u, int v) {
        for (int i : adj[u]) {
            if (i == v) {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    bool hasUniqueTopologicalSort() {
        stack<int> Stack;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        int last = Stack.top();
        Stack.pop();
        while (!Stack.empty()) {
            int current = Stack.top();
            Stack.pop();
            if (!isEdge(last, current)) {
                return false;
            }
            last = current;
        }
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

    cout << "Nhập cạnh (đỉnh nguồn, đỉnh đích của mỗi cạnh):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    if (g.hasUniqueTopologicalSort())
        cout << "Đồ thị có thứ tự tô pô duy nhất." << endl;
    else
        cout << "Đồ thị không có thứ tự tô pô duy nhất." << endl;

    return 0;
}