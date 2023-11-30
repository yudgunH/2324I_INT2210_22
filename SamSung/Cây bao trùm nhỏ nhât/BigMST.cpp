#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w): src(s), dest(d), weight(w) {}
};

class Graph {
    int V;  // Số lượng đỉnh
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap cho các cạnh
    vector<bool> inMST; // Đánh dấu các đỉnh đã được thêm vào MST

public:
    Graph(int V): V(V), inMST(V, false) {}

    void addEdge(int src, int dest, int weight) {
        pq.push(make_pair(weight, src));  // Giả định rằng src là đỉnh bắt đầu
    }

    void primMST() {
        // Bắt đầu từ đỉnh 0 (hoặc bất kỳ đỉnh nào)
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            int weight = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue; // Bỏ qua nếu đỉnh đã trong MST
            inMST[u] = true; // Đánh dấu đỉnh là đã thêm vào MST

            cout << "Thêm cạnh với trọng số " << weight << " vào MST" << endl;

            // Thêm các cạnh kề với đỉnh u vào hàng đợi
            // Code này giả định rằng bạn có thể truy cập đến các cạnh từ đỉnh u
            // Ví dụ: bạn có thể cần đọc từng phần tiếp theo của tệp tại đây
        }
    }
};

int main() {
    int V, E;
    cout << "Nhap so luong dinh (V): ";
    cin >> V;
    cout << "Nhap so luong canh (E): ";
    cin >> E;

    Graph g(V);

    cout << "Nhap cac canh va trong so cua chung (dinh nguon, dinh dich, trong so):" << endl;
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        g.addEdge(src, dest, weight);
    }

    g.primMST(); // Xây dựng MST

    return 0;
}