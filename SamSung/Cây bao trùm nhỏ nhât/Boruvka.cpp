#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class Graph {
    int V, E;
    vector<Edge> edges;

    int find(vector<int> &parent, int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    void unite(vector<int> &parent, vector<int> &rank, int x, int y) {
        int xroot = find(parent, x), yroot = find(parent, y);
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

public:
    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    void boruvkaMST() {
        vector<int> cheapest(V, -1);
        vector<int> parent(V), rank(V, 0);
        iota(parent.begin(), parent.end(), 0);

        int numTrees = V;
        int MSTweight = 0;

        while (numTrees > 1) {
            for (int v = 0; v < V; ++v)
                cheapest[v] = -1;

            for (int i = 0; i < E; i++) {
                int set1 = find(parent, edges[i].src);
                int set2 = find(parent, edges[i].dest);

                if (set1 != set2) {
                    if (cheapest[set1] == -1 || edges[cheapest[set1]].weight > edges[i].weight)
                        cheapest[set1] = i;

                    if (cheapest[set2] == -1 || edges[cheapest[set2]].weight > edges[i].weight)
                        cheapest[set2] = i;
                }
            }

            for (int i = 0; i < V; i++) {
                if (cheapest[i] != -1) {
                    int set1 = find(parent, edges[cheapest[i]].src);
                    int set2 = find(parent, edges[cheapest[i]].dest);

                    if (set1 != set2) {
                        MSTweight += edges[cheapest[i]].weight;
                        unite(parent, rank, set1, set2);
                        numTrees--;
                    }
                }
            }
        }

        cout << "Weight of MST is " << MSTweight << endl;
    }
};

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    Graph g(V, E);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.boruvkaMST();

    return 0;
}