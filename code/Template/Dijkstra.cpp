#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

#define MAXM 10001
#define MAXN 10001

#define INF 0x3f3f3f3f

struct Edge {
    int next ,to, w;
};

Edge e[MAXM];
int ec;
int dis[MAXN];
int first[MAXN];
bool vis[MAXN];
int n, m;

void addEdge(int from, int to, int w) {
    ec++;
    e[ec].to = to;
    e[ec].w = w;
    e[ec].next = first[from];
    first[from] = ec;
}

void dijkstra(int s) {
    priority_queue<pair<int, int> > q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = first[u]; i; i = e[i].next) {
            int v = e[i].to;
            int d = e[i].w + dis[u];
            if (dis[v] > d) {
                dis[v] = d;
                q.push(make_pair(-d, v));
            }
        }
    }
}

int main() {
    int s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dijkstra(s);
    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << ' ';
    }
    cout << endl;
    return 0;
}