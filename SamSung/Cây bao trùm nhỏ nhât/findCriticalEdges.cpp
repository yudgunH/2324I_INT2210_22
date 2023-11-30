#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;

    Edge() : src(0), dest(0), weight(0) {}

    Edge(int src, int dest, int weight)
        : src(src), dest(dest), weight(weight) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator==(const Edge& other) const {
        return src == other.src && dest == other.dest && weight == other.weight;
    }
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    int find(vector<int> &parent, int i) {
        if (parent[i] == i)
            return i;
        return find(parent, parent[i]);
    }

    void Union(vector<int> &parent, vector<int> &rank, int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    vector<Edge> KruskalMST() {
        vector<Edge> result;
        sort(edges.begin(), edges.end());

        vector<int> parent(V);
        vector<int> rank(V, 0);
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }

        for (Edge &e : edges) {
            int x = find(parent, e.src);
            int y = find(parent, e.dest);

            if (x != y) {
                result.push_back(e);
                Union(parent, rank, x, y);
            }
        }
        return result;
    }

    void findCriticalEdges() {
        vector<Edge> mst = KruskalMST();
        vector<Edge> criticalEdges;

        for (Edge &removedEdge : mst) {
            vector<Edge> remainingEdges;
            for (Edge &e : edges) {
                if (!(e == removedEdge)) {
                    remainingEdges.push_back(e);
                }
            }

            Graph g(V, E - 1);
            g.edges = remainingEdges;
            vector<Edge> newMST = g.KruskalMST();

            int mstWeight = 0, newMSTWeight = 0;
            for (Edge &edge : mst) mstWeight += edge.weight;
            for (Edge &edge : newMST) newMSTWeight += edge.weight;

            if (newMSTWeight > mstWeight) {
                criticalEdges.push_back(removedEdge);
            }
        }

        cout << "Critical Edges:\n";
        for (Edge &e : criticalEdges) {
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

    g.findCriticalEdges();

    return 0;
}