#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Edge {
public:
    int src, dest, weight;

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
        edges.push_back({src, dest, weight});
    }

    int find(unordered_map<int, int> &parent, int i) {
        if (parent.find(i) == parent.end() || parent[i] == i)
            return i;
        return find(parent, parent[i]);
    }

    void Union(unordered_map<int, int> &parent, vector<int> &rank, int x, int y) {
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

    void VyssotskyMST() {
        vector<Edge> result;
        unordered_map<int, int> parent;
        vector<int> rank(V, 0);

        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        for (Edge &e : edges) {
            int x = find(parent, e.src);
            int y = find(parent, e.dest);

            if (x != y) {
                result.push_back(e);
                Union(parent, rank, e.src, e.dest);
            } else {
                Edge maxEdge = e;
                for (Edge &edgeInCycle : result) {
                    if (edgeInCycle.weight > maxEdge.weight) {
                        maxEdge = edgeInCycle;
                    }
                }
                if (!(maxEdge == e)) {
                    result.erase(remove_if(result.begin(), result.end(),
                        [&maxEdge](const Edge& edge) { return edge == maxEdge; }), result.end());
                    result.push_back(e);
                }
            }
        }

        cout << "Cac canh trong cay bao trum nho nhat:\n";
        for (Edge &e : result) {
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

    g.VyssotskyMST();

    return 0;
}
