#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct EdgeHash {
    size_t operator()(const pair<int, int>& edge) const {
        return hash<int>()(edge.first) ^ hash<int>()(edge.second);
    }
};

int countParallelEdges(vector<pair<int, int>>& edges) {
    unordered_map<pair<int, int>, int, EdgeHash> edgeCount;
    for (auto& edge : edges) {
        pair<int, int> edgeKey = minmax(edge.first, edge.second);
        edgeCount[edgeKey]++;
    }

    int parallelEdges = 0;
    for (auto& count : edgeCount) {
        if (count.second > 1)
            parallelEdges += count.second - 1;
    }
    return parallelEdges;
}

int main() {
    int n;
    cout << "Nhập số lượng cạnh: ";
    cin >> n;

    vector<pair<int, int>> edges;
    cout << "Nhập cạnh (dạng u v):" << endl;
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    int parallelEdgeCount = countParallelEdges(edges);
    cout << "Số cạnh song song trong đồ thị: " << parallelEdgeCount << endl;
    return 0;
}
