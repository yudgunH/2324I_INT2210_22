#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int V;    
    list<int> *adj;

    void SCCUtil(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& stackMember) {
        static int time = 0;
        disc[u] = low[u] = ++time;
        st.push(u);
        stackMember[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                SCCUtil(v, disc, low, st, stackMember);
                low[u] = min(low[u], low[v]);
            } else if (stackMember[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            while (st.top() != u) {
                int w = st.top();
                cout << w << " ";
                stackMember[w] = false;
                st.pop();
            }
            cout << st.top() << endl;
            stackMember[st.top()] = false;
            st.pop();
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void SCC() {
        vector<int> disc(V, -1), low(V, -1);
        vector<bool> stackMember(V, false);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                SCCUtil(i, disc, low, st, stackMember);
            }
        }
    }
};

int main() {
    int V, E;
    cout << "Nhập số lượng đỉnh (V): ";
    cin >> V;

    Graph g(V);

    cout << "Nhập số lượng cạnh (E): ";
    cin >> E;

    cout << "Nhập cạnh (đỉnh nguồn đỉnh đích của mỗi cạnh):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Các thành phần liên thông mạnh trong đồ thị:\n";
    g.SCC();

    return 0;
}