#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
#define MAXM 200001
#define INF 0x3f3f3f3f

struct Node {
	int l, r, val;
};

struct Edge {
	int next, to, w;
};

int	 n, m, s;
Node t[MAXN << 2 | 3];
Edge e[MAXM << 1 | 1];
int	 first[MAXN];
int	 ec;
int	 dis[MAXN];
int	 ans[MAXN];
bool vis[MAXN];

inline int read() {
	int ans = 0;
	char ch = getchar();
	while (!isdigit(ch)) {
		ch = getchar();
	}
	while (isdigit(ch)) {
		ans = ans * 10 + ch - '0';
		ch	= getchar();
	}
	return ans;
}

inline void addEdge(int from, int to, int w) {
	e[++ec].w	= w;
	e[ec].to	= to;
	e[ec].next	= first[from];
	first[from] = ec;
}

inline void pushUp(int rt) {
	t[rt].val = (dis[t[rt << 1].val] < dis[t[rt << 1 | 1].val] ? t[rt << 1].val : t[rt << 1 | 1].val);
}

void build(int rt, int l, int r) {
	t[rt].l = l, t[rt].r = r;
	if (l == r) {
		t[rt].val = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushUp(rt);
}

void update(int rt, int pos) {
	if (t[rt].l == pos && t[rt].r == pos) {
		return;
	}
	int mid = (t[rt].l + t[rt].r) >> 1;
	if (pos <= mid)
		update(rt << 1, pos);
	else
		update(rt << 1 | 1, pos);
	pushUp(rt);
}

void dijkstra(int s) {
	memset(dis, 0x3f, sizeof(dis));
	memset(ans, 0x3f, sizeof(ans));
	ans[s] = dis[s] = 0;
	build(1, 1, n);
	for (int i = 1; i <= n; ++i) {
		int u  = t[1].val;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = first[u]; i; i = e[i].next) {
			int v = e[i].to;
			if (vis[v]) continue;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				update(1, v);
			}
		}
		ans[u] = dis[u];
		dis[u] = INF;
		update(1, u);
	}
}

int main() {
	n = read(), m = read(), s = read();
	for (int i = 1, u, v, w; i <= m; ++i) {
		u = read(), v = read(), w = read();
		addEdge(u, v, w);
	}
	dijkstra(s);
	for (int i = 1; i <= n; ++i) {
		printf("%d ", (ans[i] == INF ? 0x7fffffff : ans[i]));
	}
	putchar('\n');
	return 0;
}