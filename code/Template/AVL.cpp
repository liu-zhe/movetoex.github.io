#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define ls ch[0]
#define rs ch[1]

struct Node {
	int ch[2];
	int dep, cnt, siz;
	int val;
};

Node t[100001];
int	 root;
int	 cnt;

inline int newNode(int x) {
	t[++cnt].val = x;
	t[cnt].siz	 = 1;
	t[cnt].cnt	 = 1;
	t[cnt].dep	 = 1;
	return cnt;
}

inline int dep(int rt) {
	return rt ? t[rt].dep : -1;
}

void pushUp(int rt) {
	t[rt].siz = t[t[rt].ls].siz + t[t[rt].rs].siz + t[rt].cnt;
	t[rt].dep = max(dep(t[rt].ls), dep(t[rt].rs)) + 1;
}

void rotate(int &rt, int chk) {
	int p			 = t[rt].ch[chk];
	t[rt].ch[chk]	 = t[p].ch[chk ^ 1];
	t[p].ch[chk ^ 1] = rt;
	pushUp(rt);
	pushUp(p);
	rt = p;
}

void maintain(int &rt) {
	int fac = dep(t[rt].ls) - dep(t[rt].rs);
	if (fac > 1) {
		if (dep(t[t[rt].ls].ls) > dep(t[t[rt].ls].rs)) {
			rotate(rt, 0);
		} else {
			rotate(t[rt].ls, 1);
			rotate(rt, 0);
		}
	}
	if (fac < -1) {
		if (dep(t[t[rt].rs].rs) > dep(t[t[rt].rs].ls)) {
			rotate(rt, 1);
		} else {
			rotate(t[rt].rs, 0);
			rotate(rt, 1);
		}
	}
}

void insert(int &rt, int val) {
	if (!rt) {
		rt = newNode(val);
	} else {
		if (val == t[rt].val) {
			t[rt].cnt++;
		} else if (val < t[rt].val) {
			insert(t[rt].ls, val);
		} else if (val > t[rt].val) {
			insert(t[rt].rs, val);
		}
	}
	maintain(rt);
	pushUp(rt);
}

int max(int rt) {
	while (t[rt].rs) {
		rt = t[rt].rs;
	}
	return rt;
}

int min(int rt) {
	while (t[rt].ls) {
		rt = t[rt].ls;
	}
	return rt;
}

void del_max(int &rt) {
	if (!t[rt].rs) {
		rt = t[rt].ls;
		return;
	} else {
		del_max(t[rt].rs);
	}
	pushUp(rt);
}

void del_min(int &rt) {
	if (!t[rt].ls) {
		rt = t[rt].rs;
		return;
	} else {
		del_min(t[rt].ls);
	}
	pushUp(rt);
}

void del(int &rt, int x) {
	if (!rt) return;
	if (t[rt].val == x) {
		--t[rt].cnt;
		if (t[rt].cnt == 0) {
			if (t[rt].ls && t[rt].rs) {
				int p = 0;
				if (dep(t[rt].ls) > dep(t[rt].rs)) {
					p		  = max(t[rt].ls);
					t[rt].val = t[p].val;
					t[rt].cnt = t[p].cnt;
					del_max(t[rt].ls);
				} else {
					p		  = min(t[rt].rs);
					t[rt].val = t[p].val;
					t[rt].cnt = t[p].cnt;
					del_min(t[rt].rs);
				}
			} else {
				rt = t[rt].ls | t[rt].rs;
			}
		}
	} else if (t[rt].val > x) {
		del(t[rt].ls, x);
	} else if (t[rt].val < x) {
		del(t[rt].rs, x);
	}
	maintain(rt);
	pushUp(rt);
}

int rk(int x) {
	int rt	= root;
	int ans = 1;
	while (rt) {
		if (x < t[rt].val) {
			rt = t[rt].ls;
		} else {
			ans += t[t[rt].ls].siz;
			if (t[rt].val == x) return ans;
			ans += t[rt].cnt;
			rt = t[rt].rs;
		}
	}
	return ans;
}

int kth(int k) {
	int rt = root;
	while (rt) {
		if (t[rt].ls && k <= t[t[rt].ls].siz) {
			rt = t[rt].ls;
		} else {
			k -= t[t[rt].ls].siz + t[rt].cnt;
			if (k <= 0) return t[rt].val;
			rt = t[rt].rs;
		}
	}
	return 0;
}

int pre(int val) {
	return kth(rk(val) - 1);
}

int nxt(int val) {
	return kth(rk(val + 1));
}

int n, opt, x;

int main() {
	cin >> n;
	while (n-- > 0) {
		cin >> opt >> x;
		if (opt == 1) {
			insert(root, x);
		} else if (opt == 2) {
			del(root, x);
		} else if (opt == 3) {
			cout << rk(x) << endl;
		} else if (opt == 4) {
			cout << kth(x) << endl;
		} else if (opt == 5) {
			cout << pre(x) << endl;
		} else if (opt == 6) {
			cout << nxt(x) << endl;
		}
	}
	return 0;
}