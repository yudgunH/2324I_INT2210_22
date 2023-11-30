#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

void addEdge(vector<vector<Edge>>& adj, int u, int v, int vertexWeight) {
    adj[u].push_back(Edge(v, vertexWeight));
}

vector<int> dijkstra(const vector<vector<Edge>>& adj, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(adj.size(), INT_MAX);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<int> vertexWeights(n);
    cout << "Enter vertex weights: ";
    for (int i = 0; i < n; ++i) {
        cin >> vertexWeights[i];
    }

    vector<vector<Edge>> adj(n);

    cout << "Enter edges (u, v): ";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v, vertexWeights[v]);
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<int> distances = dijkstra(adj, src);

    cout << "Shortest distances from vertex " << src << ":\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Vertex " << i << ": unreachable\n";
        } else {
            cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    return 0;
}
