#include <bits/stdc++.h>

#define MAXN 50001
#define MAXM 100001

using namespace std;

struct Edge {
	int next, to;
};

struct Node {
	int l, r;
	int val, tag;
	Node *ls, *rs;
	Node() = default;
};

int n, m;
Node* root = new Node();
Edge e[MAXM];
int first[MAXN];
int ec;
int seg[MAXN];
int son[MAXN];
int siz[MAXN];
int top[MAXN];
int fa[MAXN];
int dep[MAXN];
int cnt;

void addEdge(int from, int to) {
	e[++ec].to = to;
	e[ec].next = first[from];
	first[from] = ec;
}

void _destroy(Node* rt) {
	if (rt) {
		if (rt->ls) _destroy(rt->ls);
		if (rt->rs) _destroy(rt->rs);
		delete rt;
	}
}

void pushUp(Node* rt) {
	rt->val = max(rt->ls->val, rt->rs->val);
}

void pushDown(Node* rt) {
	if (rt->tag) {
		rt->ls->val += rt->tag;
		rt->ls->tag += rt->tag;
		rt->rs->val += rt->tag;
		rt->rs->tag += rt->tag;
		rt->tag = 0;
	}
}

void build(Node* rt, int l, int r) {
	rt->l = l, rt->r = r;
	if (l == r) {
		rt->val = 0;
		return;
	}
	rt->ls = new Node(), rt->rs = new Node();
	int mid = (l + r) >> 1;
	build(rt->ls, l, mid);
	build(rt->rs, mid + 1, r);
	pushUp(rt);
}

void add(Node* rt, int l, int r, int k) {
	if (rt->l >= l && rt->r <= r) {
		rt->val += k;
		rt->tag += k;
		return;
	}
	pushDown(rt);
	int mid = (rt->l + rt->r) >> 1;
	if (l <= mid) add(rt->ls, l, r, k);
	if (r > mid) add(rt->rs, l, r, k);
	pushUp(rt);
}

int query(Node* rt, int l, int r) {
	if (rt->l >= l && rt->r <= r) {
		return rt->val;
	}
	pushDown(rt);
	int ans = 1 << 31;
	int mid = (rt->l + rt->r) >> 1;
	if (l <= mid) ans = max(ans, query(rt->ls, l, r));
	if (r > mid) ans = max(ans, query(rt->rs, l, r));
	return ans;
}

void dfs1(int u, int f, int d) {
	fa[u] = f;
	dep[u] = d;
	siz[u] = 1;
	for (int i = first[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == f) continue;
		dfs1(v, u, d + 1);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) {
			son[u] = v;
		}
	}
}

void dfs2(int u, int t) {
	top[u] = t;
	seg[u] = ++cnt;
	if (!son[u]) return;
	dfs2(son[u], t);
	for (int i = first[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == son[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

void addTree(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		add(root, seg[top[x]], seg[x], 1);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	add(root, seg[x], seg[y], 1);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(root, 1, n);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		addTree(u, v);
	}
	cout << query(root, 1, n) << endl;
	_destroy(root);
	return 0;
}