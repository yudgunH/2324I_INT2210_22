#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge() : src(0), dest(0), weight(0) {}
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int i) {
        if (i != parent[i])
            parent[i] = find(parent[i]);
        return parent[i];
    }
    void unite(int x, int y) {
        int xroot = find(x), yroot = find(y);
        if (xroot == yroot) return;
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[yroot] < rank[xroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

class Graph {
    int V;
    vector<Edge> edges;
public:
    Graph(int V) : V(V) {}
    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }
    vector<Edge> findMSTWithEdges(const vector<Edge>& includeEdges) {
        UnionFind uf(V);
        vector<Edge> result;
        for (const Edge& e : includeEdges) {
            result.push_back(e);
            uf.unite(e.src, e.dest);
        }
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });
        for (const Edge& e : edges) {
            if (uf.find(e.src) != uf.find(e.dest)) {
                uf.unite(e.src, e.dest);
                result.push_back(e);
            }
        }
        return result;
    }
};

int main() {
    int V, E, S;
    cout << "Nhap so luong dinh (V): ";
    cin >> V;
    cout << "Nhap so luong canh (E): ";
    cin >> E;

    Graph g(V);
    cout << "Nhap cac canh cua do thi (dinh nguon, dinh dich, trong so):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    cout << "Nhap so luong canh cua tap S (S): ";
    cin >> S;
    vector<Edge> includeEdges;
    cout << "Nhap cac canh cua tap S (dinh nguon, dinh dich, trong so):\n";
    for (int i = 0; i < S; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        includeEdges.emplace_back(u, v, w);
    }

    vector<Edge> mst = g.findMSTWithEdges(includeEdges);

    cout << "Cac canh trong MST:\n";
    for (const Edge& e : mst) {
        cout << e.src << " -- " << e.dest << " == " << e.weight << '\n';
    }

    return 0;
}