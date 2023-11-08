#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector<int> topological_sort(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    for (const auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
        indegree[edge.second]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return result;
}

int main() {
    ifstream input("jobs.txt");
    ofstream output("jobs.out");
    
    int n, m;
    input >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        edges.push_back({u, v});
    }
    vector<int> sorted_jobs = topological_sort(n, edges);
    for (int job : sorted_jobs) {
        output << job << " ";
    }
    output << endl;

    return 0;
}