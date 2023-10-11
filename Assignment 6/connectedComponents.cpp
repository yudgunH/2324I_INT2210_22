#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include<vector>

using namespace std;

int n, m;
vector<int> graph[1001];
bool visited[1001];

void dfs(int u) {
    visited[u] = true;
    for(int v: graph[u]) {
        if(!visited[v]) {
            dfs(v);
        }
    }
}


void bfs(int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        // cout << v << " ";
        for(int x: graph[v]) {
            if(!visited[x]) {
                q.push(x);
                visited[x] = true;
            }
        }
    }
    
}

void connectedComponents() {
    int cnt = 0;
    memset(visited, false, sizeof(visited));
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            ++cnt;
            dfs(i);
        }
    }
    cout << cnt << endl;
}

int main () {
    cin >> n >> m;
    for(int i = 0; i< m; i++) {
        int x, y;   cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    connectedComponents();
    return 0;
}