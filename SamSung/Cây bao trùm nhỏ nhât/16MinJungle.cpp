#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge {
public:
    int src, dest, weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    int find(vector<int> &parent, int i) {
        if (parent[i] == -1)
            return i;
        return parent[i] = find(parent, parent[i]);
    }

    void Union(vector<int> &parent, vector<int> &rank, int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[yroot] < rank[xroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void KruskalMST() {
        vector<Edge> result;
        vector<int> parent(V, -1);
        vector<int> rank(V, 0);

        sort(edges.begin(), edges.end(),
                  [](Edge a, Edge b) { return a.weight < b.weight; });

        for (Edge e : edges) {
            int x = find(parent, e.src);
            int y = find(parent, e.dest);

            if (x != y) {
                result.push_back(e);
                Union(parent, rank, x, y);
            }
        }

        cout << "Cac canh trong rung bao trum nho nhat:\n";
        for (Edge e : result)
            cout << e.src << " -- " << e.dest << " == " << e.weight << endl;
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

    g.KruskalMST();

    return 0;
}