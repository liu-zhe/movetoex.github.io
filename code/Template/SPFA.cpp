#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;

#define MAXN 10001
#define MAXM 10001
#define INF 0x3f3f3f3f

#define DIRECTED

struct Edge {
    int next, to, w;
};

Edge e[MAXM];
bool vis[MAXN];
int ec;
int first[MAXN];
int dis[MAXN];
int n, m;
int s;

inline void addEdge(int from, int to, int w) {
    ec++;
    e[ec].to = to;
    e[ec].w = w;
    e[ec].next = first[from];
    first[from] = ec;
}

void SPFA(int s) {
	queue<int> q;
	memset(vis, 1, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = first[u]; i; i = e[i].next) {
			int v = e[i].to;
			int d = dis[u] + e[i].w;
			if (dis[v] > d) {
				dis[v] = d;
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}

int main() {
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
#ifndef DIRECTED
        addEdge(v, u, w);
#endif
    }
    SPFA(s);
    for (int i = 1; i <= n; ++i) {
        cout << (dis[i] == INF ? 0x7fffffff : dis[i]) << ' ';
    }
    cout << endl;
    return 0;
}