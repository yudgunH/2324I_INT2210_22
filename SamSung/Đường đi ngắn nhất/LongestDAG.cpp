#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

void addEdge(vector<vector<Edge>>& adj, int u, int v, int w) {
    adj[u].push_back(Edge(v, w));
}

void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack, vector<vector<Edge>>& adj) {
    visited[v] = true;

    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
        Edge edge = *i;
        if (!visited[edge.to]) {
            topologicalSortUtil(edge.to, visited, Stack, adj);
        }
    }

    Stack.push(v);
}

vector<int> longestPathDAG(vector<vector<Edge>>& adj, int V, int s) {
    stack<int> Stack;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, Stack, adj);
        }
    }

    vector<int> distances(V, INT_MIN);
    distances[s] = 0;

    while (!Stack.empty()) {
        int u = Stack.top();
        Stack.pop();

        if (distances[u] != INT_MIN) {
            for (Edge e : adj[u]) {
                if (distances[e.to] < distances[u] + e.weight) {
                    distances[e.to] = distances[u] + e.weight;
                }
            }
        }
    }

    return distances;
}

int main() {
    int V = 6;
    vector<vector<Edge>> adj(V);

    addEdge(adj, 0, 1, 5);
    addEdge(adj, 0, 2, 3);
    addEdge(adj, 1, 3, 6);
    addEdge(adj, 1, 2, 2);
    addEdge(adj, 2, 4, 4);
    addEdge(adj, 2, 5, 2);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 3, 5, 1);
    addEdge(adj, 3, 4, -1);
    addEdge(adj, 4, 5, -2);

    int s = 1; // Đỉnh bắt đầu
    vector<int> distances = longestPathDAG(adj, V, s);

    cout << "Longest distances from vertex " << s << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MIN ? "unreachable" : to_string(distances[i])) << "\n";
    }

    return 0;
}
