#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

struct Point {
    double x, y;
};

struct Edge {
    int to;
    double weight;
};

double euclideanDistance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void addEdge(vector<vector<Edge>>& graph, int u, int v, double weight) {
    graph[u].push_back({v, weight});
}

vector<double> dijkstra(const vector<vector<Edge>>& graph, int src) {
    int n = graph.size();
    vector<double> dist(n, INT_MAX);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            double weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter coordinates for vertex " << i << " (x y): ";
        cin >> points[i].x >> points[i].y;
    }

    vector<vector<Edge>> graph(n);
    cout << "Enter number of edges: ";
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cout << "Enter edge (u v): ";
        cin >> u >> v;

        double weight = euclideanDistance(points[u], points[v]);
        addEdge(graph, u, v, weight);
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<double> distances = dijkstra(graph, src);

    cout << "Shortest distances from vertex " << src << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "To vertex " << i << ": " << distances[i] << "\n";
    }

    return 0;
}
