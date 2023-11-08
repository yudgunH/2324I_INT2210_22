#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int MAX = 1e5 + 5;
int parent[MAX], rankNode[MAX];

struct Edge {
    int u, v, w;
    bool operator<(Edge const& other) {
        return w < other.w;
    }
};

vector<Edge> edges, result;

int findSet(int i) {
    if (i != parent[i]) {
        parent[i] = findSet(parent[i]);
    }
    return parent[i];
}

void unionSet(int i, int j) {
    int x = findSet(i);
    int y = findSet(j);
    if (x != y) {
        if (rankNode[x] > rankNode[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
            if (rankNode[x] == rankNode[y]) {
                rankNode[y]++;
            }
        }
    }
}

int main() {
    ifstream input("connection.txt");
    ofstream output("connection.out");
    int n, m;
    input >> n >> m;
    for (int i = 0; i < m; i++) {
        Edge edge;
        input >> edge.u >> edge.v >> edge.w;
        edges.push_back(edge);
    }
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rankNode[i] = 0;
    }
    sort(edges.begin(), edges.end());
    int totalCost = 0;
    for (Edge e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            totalCost += e.w;
            result.push_back(e);
            unionSet(e.u, e.v);
        }
    }
    output << totalCost << endl;
    for (Edge e : result) {
        output << e.u << " " << e.v << " " << e.w << endl;
    }
    input.close();
    output.close();
    return 0;
}