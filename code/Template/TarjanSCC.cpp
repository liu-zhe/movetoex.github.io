#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int next, to;
	Edge() {}
};

Edge e[10001];
int ec;
int first[10001];
int n, m, s;
int sc;
int cnt;
int ans;
int dfn[10001];
int low[10001];
int scc[10001];
int sz[10001];

stack<int> st;

void addEdge(int u, int v) {
	e[++ec].to = v;
	e[ec].next = first[u];
	first[u]   = ec;
}

void tarjan(int u) {
	low[u] = dfn[u] = ++cnt;
	st.push(u);
	for (int i = first[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (!scc[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		++sc;
		while (st.top() != u) {
			scc[st.top()] = sc;
			++sz[sc];
			st.pop();
		}
		scc[u] = sc;
		++sz[sc];
		st.pop();
	}
}

int main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		addEdge(u, v);
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) tarjan(i);
	}
	for (int i = 1; i <= n; ++i) {
		cout << scc[i] << ' ';
	}
	cout << endl;
	return 0;
}