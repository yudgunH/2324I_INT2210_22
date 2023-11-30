#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph {
    int V;    
    list<int> *adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void BFS(int s) {
        vector<int> distance(V, -1);
        queue<int> queue;

        distance[s] = 0;
        queue.push(s);

        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();

            for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
                if (distance[*i] == -1) {
                    distance[*i] = distance[u] + 1;
                    queue.push(*i);
                }
            }
        }

        cout << "Khoảng cách từ đỉnh " << s << " đến các đỉnh khác trong đồ thị:" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Đỉnh " << i << ": " << distance[i] << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    int startVertex = 0;
    g.BFS(startVertex);

    return 0;
}