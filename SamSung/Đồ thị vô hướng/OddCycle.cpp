/*Nếu một đồ thị là đồ thị hai màu, thì nó không chứa chu trình độ dài lẻ.
Nếu một đồ thị không chứa chu trình độ dài lẻ, thì nó là đồ thị hai màu.*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Color { NONE, RED, BLUE };

bool isBipartite(vector<vector<int>>& graph, int start, vector<Color>& colors) {
    colors[start] = RED;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (colors[v] == NONE) {
                colors[v] = (colors[u] == RED) ? BLUE : RED;
                q.push(v);
            } else if (colors[v] == colors[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int V, E;
    cout << "Nhập số đỉnh (V): ";
    cin >> V;
    cout << "Nhập số cạnh (E): ";
    cin >> E;

    vector<vector<int>> graph(V);
    vector<Color> colors(V, NONE);

    cout << "Nhập cạnh (dạng u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool bipartite = true;
    for (int i = 0; i < V; ++i) {
        if (colors[i] == NONE) {
            if (!isBipartite(graph, i, colors)) {
                bipartite = false;
                break;
            }
        }
    }

    if (bipartite)
        cout << "Đồ thị là đồ thị hai màu." << endl;
    else
        cout << "Đồ thị không phải là đồ thị hai màu và chứa chu trình lẻ." << endl;

    return 0;
}
