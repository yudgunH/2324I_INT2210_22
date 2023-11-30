#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

class Graph {
    int V;
    vector<vector<Edge>> adj;
    vector<Edge> edges;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int src, int dest, int weight) {
        adj[src].push_back(Edge(src, dest, weight));
        adj[dest].push_back(Edge(dest, src, weight));
        edges.push_back(Edge(src, dest, weight));
    }

    void primLazy() {
        vector<bool> inMST(V, false);
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        int src = 0;
        inMST[src] = true;

        for (auto& e : adj[src]) {
            pq.push(e);
        }

        while (!pq.empty()) {
            Edge edge = pq.top();
            pq.pop();
            int dest = edge.dest;

            if (inMST[dest]) continue;

            inMST[dest] = true;
            cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;

            for (auto& e : adj[dest]) {
                if (!inMST[e.dest]) {
                    pq.push(e);
                }
            }
        }
    }

    void primPriorityQueue() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> key(V, numeric_limits<int>::max());
        vector<bool> inMST(V, false);
        vector<int> parent(V, -1);

        key[0] = 0;
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto& e : adj[u]) {
                int v = e.dest;
                int weight = e.weight;

                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; ++i) {
            if (parent[i] != -1) {
                cout << parent[i] << " -- " << i << " : " << key[i] << endl;
            }
        }
    }

    void kruskal() {
        vector<Edge> result;
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V);
        iota(parent.begin(), parent.end(), 0);
        vector<int> rank(V, 0);

        auto find = [&](int i) -> int {
            if (parent[i] != i)
                parent[i] = find(parent[i]);
            return parent[i];
        };

        auto unite = [&](int x, int y) {
            int xroot = find(x), yroot = find(y);
            if (rank[xroot] < rank[yroot]) parent[xroot] = yroot;
            else if (rank[xroot] > rank[yroot]) parent[yroot] = xroot;
            else { parent[yroot] = xroot; rank[xroot]++; }
        };

        for (auto& e : edges) {
            int x = find(e.src), y = find(e.dest);
            if (x != y) {
                result.push_back(e);
                unite(x, y);
            }
        }

        for (auto& e : result) {
            cout << e.src << " -- " << e.dest << " : " << e.weight << endl;
        }
    }
};

int main() {
    int V = 6; // Number of vertices
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 6);
    g.addEdge(1, 2, 6);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 3);
    g.addEdge(4, 5, 7);

    auto start = chrono::high_resolution_clock::now();
    g.primLazy();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time for Prim's Lazy: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    g.primPriorityQueue();
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time for Prim's Priority Queue: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    g.kruskal();
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time for Kruskal's: " << duration.count() << " seconds" << endl;

    return 0;
}