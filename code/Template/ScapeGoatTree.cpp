#include <bits/stdc++.h>

using namespace std;

struct ScapeGoatTree {
	struct Node {
		int	 ch[2];
		int	 val;
		int	 siz;
		int	 valid;
		bool exi;
	};

	Node   t[200001];
	int	   cnt = 0;
	int	   root = 0;
	int	   cur[100001];

	double alpha = 0.75;

	inline void pushUp(int rt) {
		t[rt].siz	= t[t[rt].ch[0]].siz + t[t[rt].ch[1]].siz + t[rt].exi;
		t[rt].valid = t[t[rt].ch[0]].valid + t[t[rt].ch[1]].valid + t[rt].exi;
	}

	inline bool needRebuild(int rt) {
		return t[rt].valid * alpha <= max(t[t[rt].ch[0]].valid, t[t[rt].ch[1]].valid);
	}

	void dfs(int rt) {
		if (!rt) return;
		dfs(t[rt].ch[0]);
		if (t[rt].exi) cur[++cur[0]] = rt;
		dfs(t[rt].ch[1]);
	}

	void build(int &rt, int l, int r) {
		int mid = (l + r) >> 1;
		rt		= cur[mid];
		if (l == r) {
			t[rt].ch[0] = t[rt].ch[1] = 0;
			t[rt].exi = t[rt].siz = t[rt].valid = 1;
			return;
		}
		if (l < mid) {
			build(t[rt].ch[0], l, mid - 1);
		} else {
			t[rt].ch[0] = 0;
		}
		build(t[rt].ch[1], mid + 1, r);
		pushUp(rt);
	}

	inline void rebuild(int &rt) {
		cur[0] = 0;
		dfs(rt);
		if (cur[0])
			build(rt, 1, cur[0]);
		else
			rt = 0;
	}

	void insert(int &rt, int x) {
		if (!rt) {
			rt		  = ++cnt;
			t[rt].val = x;
			t[rt].exi = t[rt].siz = t[rt].valid = 1;
			t[rt].ch[0] = t[rt].ch[1] = 0;
			return;
		}
		++t[rt].valid;
		++t[rt].siz;
		if (t[rt].val >= x) {
			insert(t[rt].ch[0], x);
		} else {
			insert(t[rt].ch[1], x);
		}
		if (needRebuild(rt)) {
			rebuild(rt);
		}
	}

	inline int rk(int x) {
		int rt	= root;
		int ans = 1;
		while (rt) {
			if (t[rt].val >= x) {
				rt = t[rt].ch[0];
			} else {
				ans += t[t[rt].ch[0]].valid + t[rt].exi;
				rt = t[rt].ch[1];
			}
		}
		return ans;
	}

	inline int kth(int k) {
		int rt = root;
		while (rt) {
			if (t[rt].exi && t[t[rt].ch[0]].valid + t[rt].exi == k) {
				return t[rt].val;
			} else if (t[t[rt].ch[0]].valid >= k) {
				rt = t[rt].ch[0];
			} else {
				k -= t[t[rt].ch[0]].valid + t[rt].exi;
				rt = t[rt].ch[1];
			}
		}
		return 0;
	}

	void del(int &rt, int k) {
		--t[rt].valid;
		if (t[rt].exi && t[t[rt].ch[0]].valid + t[rt].exi == k) {
			t[rt].exi = 0;
			return;
		}
		if (t[t[rt].ch[0]].valid + t[rt].exi >= k) {
			del(t[rt].ch[0], k);
		} else {
			del(t[rt].ch[1], k - t[t[rt].ch[0]].valid - t[rt].exi);
		}
	}

	inline void del(int x) {
		del(root, rk(x));
		if (t[root].siz * alpha > t[root].valid) {
			rebuild(root);
		}
	}

	inline int pre(int x) {
		return kth(rk(x) - 1);
	}

	inline int nxt(int x) {
		return kth(rk(x + 1));
	}
};

int n;
ScapeGoatTree t;

int main() {
	cin >> n;
	while (n-- > 0) {
		int opt, x;
		cin >> opt >> x;
		if (opt == 1) {
			t.insert(t.root, x);
		} else if (opt == 2) {
			t.del(x);
		} else if (opt == 3) {
			cout << t.rk(x) << endl;
		} else if (opt == 4) {
			cout << t.kth(x) << endl;
		} else if (opt == 5) {
			cout << t.pre(x) << endl;
		} else {
			cout << t.nxt(x) << endl;
		}
	}
	return 0;
}