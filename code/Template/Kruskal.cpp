#include <iostream>
#include <algorithm>

using namespace std;

#define MAXM 10001
#define MAXN 10001

struct Edge {
	int from, to, w;
	bool operator <(Edge& other) {
		return this->w < other.w;
	}
};

struct UFS {
	int f[MAXN];
	void init(int x) { for (int i = 1; i <= x; ++i) f[i] = i; }
	int getf(int x) { return f[x] == x ? x : f[x] = getf(f[x]); }
	bool same(int a, int b) { return getf(a) == getf(b); }
	void merge(int a, int b) { if (!same(a, b)) f[getf(b)] = getf(a); }
};

int n, m;
Edge e[MAXM];
int ec;
UFS f;

inline void addEdge(int from, int to, int w) {
	ec++;
	e[ec].from = from;
	e[ec].to = to;
	e[ec].w = w;
}

inline int kruskal() {
	int ans = 0;
	f.init(n);
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= m;++i) {
		int a = f.getf(e[i].from);
		int b = f.getf(e[i].to);
		if (a != b) {
			ans += e[i].w;
			f.merge(a, b);
		}
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	cout << kruskal() << endl;
	return 0;
}