#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Graph {
    int V;
    vector<int> *adj;

public:
    Graph(int V) : V(V), adj(new vector<int>[V]) {}

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void topologicalSort() {
        vector<int> indegree(V, 0);

        // Tính bậc vào (indegree) cho mỗi đỉnh
        for (int i = 0; i < V; ++i) {
            for (int j : adj[i]) {
                indegree[j]++;
            }
        }

        // Thêm tất cả các đỉnh có bậc vào bằng 0 vào hàng đợi
        queue<int> q;
        for (int i = 0; i < V; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Duyệt cho đến khi hàng đợi rỗng
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            // Cho mỗi đỉnh kề với đỉnh v
            for (int u : adj[v]) {
                // Giảm bậc vào của đỉnh kề đi 1
                if (--indegree[u] == 0) {
                    q.push(u);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Nhap so luong dinh (V): ";
    cin >> V;
    cout << "Nhap so luong canh (E): ";
    cin >> E;

    Graph g(V);

    cout << "Nhap cac canh (dinh nguon, dinh dich cua moi canh):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Thu tu topo cua do thi la: ";
    g.topologicalSort();

    return 0;
}