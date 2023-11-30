#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
};

class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
            if (rank[x] == rank[y])
                rank[y]++;
        }
    }
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    void reverseDeleteMST() {
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight > b.weight;
        });

        DisjointSet ds(V);
        vector<Edge> mst;

        for (auto &e : edges) {
            int x = ds.find(e.src);
            int y = ds.find(e.dest);

            if (x != y) {
                mst.push_back(e);
                ds.merge(x, y);
            }
        }

        cout << "Cac canh trong cay bao trum nho nhat:\n";
        for (auto &e : mst) {
            cout << e.src << " -- " << e.dest << " == " << e.weight << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Nhap so luong dinh (V): ";
    cin >> V;
    cout << "Nhap so luong canh (E): ";
    cin >> E;

    Graph g(V, E);

    cout << "Nhap cac canh va trong so cua chung (dinh nguon, dinh dich, trong so):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.reverseDeleteMST();

    return 0;
}