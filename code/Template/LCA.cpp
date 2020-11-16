#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct Edge {
	int next, to;
};

int n, m, s;
Edge e[500001 << 1];
int first[500001];
int edgeCnt;
int fa[500001][21];
int dep[500001];
int _log[500001];

void addEdge(int from, int to) {
	e[++edgeCnt].to = to;
	e[edgeCnt].next = first[from];
	first[from] = edgeCnt;
}

void dfs(int u, int fath) {
	fa[u][0] = fath;
	dep[u] = dep[fath] + 1;
	for (int i = 1; i <= _log[dep[u]]; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = first[u]; i; i = e[i].next) {
		if (e[i].to != fath) dfs(e[i].to, u);
	}
}

int lca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	while (dep[a] > dep[b]) {
		a = fa[a][_log[dep[a] - dep[b]] - 1];
	}
	if (a == b) return a;
	for (int i = _log[dep[a]] - 1; i >= 0; --i) {
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	}
	return fa[a][0];
}

int main() {
    ios::sync_with_stdio(false);
	cin >> n >> m >> s;
	for (int i = 1; i <= n; ++i) {
		_log[i] = _log[i - 1] + ((1 << _log[i - 1]) == i);
	}
	for (int i = 1; i < n; ++i) {
		int from, to;
		cin >> from >> to;
		addEdge(from, to);
		addEdge(to, from);
	}
	dfs(s, 0);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << endl;
	}
	return 0;
}