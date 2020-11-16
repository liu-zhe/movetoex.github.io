#include <bits/stdc++.h>

using namespace std;

#define ls ch[0]
#define rs ch[1]

struct Node {
    int val, fa, ch[2], cnt, siz;
};
Node t[100001];
int cnt;
int root;

int newNode(int val, int fa = 0) {
    ++cnt;
    t[cnt].val = val;
    t[cnt].fa = fa;
    t[cnt].siz = t[cnt].cnt = 1;
    t[cnt].ls = t[cnt].rs = 0;
    return cnt;
}

void pushUp(int rt) { t[rt].siz = t[t[rt].ls].siz + t[t[rt].rs].siz + t[rt].cnt; }

int identify(int rt) { return t[t[rt].fa].rs == rt; }

void destroy(int rt) { memset(t + rt, 0, sizeof(Node)); }

void connect(int rt, int fa, int ch) {
    t[rt].fa = fa;
    t[fa].ch[ch] = rt;
}

void rotate(int x) {
    int y = t[x].fa;
    int z = t[y].fa;
    int chk = identify(x);
    connect(t[x].ch[chk ^ 1], y, chk);
    connect(y, x, chk ^ 1);
    t[x].fa = z;
    if (z) {
        t[z].ch[y == t[z].rs] = x;
	}
    pushUp(y);
    pushUp(x);
}

void splay(int x, int to = root) {
	to = t[to].fa;
	while (t[x].fa != to) {
		int f = t[x].fa;
		if (!t[f].fa) {
			rotate(x);
			break;
		}
        if (identify(x) == identify(f)) {
			rotate(f);
			rotate(x);
		}
		else {
			rotate(x);
			rotate(x);
		}
    }
	if (!to) {
		root = x;
	}
}

void insert(int x) {
    if (!root) {
        root = newNode(x);
        return;
    }
    int rt = root;
    while (rt) {
		++t[rt].siz;
        if (t[rt].val == x) {
            ++t[rt].cnt;
            splay(rt);
            break;
        }
        int nxt = (t[rt].val < x);
        if (!t[rt].ch[nxt]) {
            t[rt].ch[nxt] = newNode(x, rt);
            splay(t[rt].ch[nxt]);
            break;
        }
        rt = t[rt].ch[nxt];
    }
}

int rk(int k) {
    int ans = 1, rt = root;
    while (rt) {
        if (k < t[rt].val) {
            rt = t[rt].ls;
        } else {
            ans += t[t[rt].ls].siz;
            if (t[rt].val == k) {
                splay(rt);
                return ans;
            }
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
            k -= t[rt].cnt + t[t[rt].ls].siz;
            if (k <= 0) {
                return t[rt].val;
			}
            rt = t[rt].rs;
        }
    }
    return 0;
}

int pre() {
    int rt = t[root].ls;
    while (t[rt].rs) {
        rt = t[rt].rs;
	}
    return rt;
}

int nxt() {
    int rt = t[root].rs;
    while (t[rt].ls) {
        rt = t[rt].ls;
	}
    return rt;
}

void del(int k) {
    rk(k);
    int rt = root;
    if (t[rt].cnt > 1) {
        --t[rt].cnt;
        pushUp(rt);
        return;
    }
    if (!t[rt].ls && !t[rt].rs) {
        root = 0;
        return;
    }
    if (!t[root].ls) {
        root = t[rt].rs;
        t[root].fa = 0;
        return;
    }
    if (!t[rt].rs) {
        root = t[rt].ls;
        t[root].fa = 0;
        return;
    }
    int x = pre();
    rt = root;
    splay(x);
    t[t[rt].rs].fa = x;
    t[x].rs = t[rt].rs;
    pushUp(rt);
}

int n;

int main() {
    cin >> n;
    while (n-- > 0) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            insert(x);
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
            cout << rk(x) << endl;
        } else if (opt == 4) {
            cout << kth(x) << endl;
        } else if (opt == 5) {
            insert(x);
            cout << t[pre()].val << endl;
            del(x);
        } else {
            insert(x);
            cout << t[nxt()].val << endl;
            del(x);
        }
    }
    return 0;
}