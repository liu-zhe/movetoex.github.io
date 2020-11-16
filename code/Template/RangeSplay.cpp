#include <bits/stdc++.h>

using std::cin;
using std::ios;
using std::cout;
using std::endl;
using std::max;
using std::swap;

#define ls ch[0]
#define rs ch[1]

struct Node {
    int val, fa, ch[2], cnt, siz, tag;
};

Node t[2000001];
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

void reverse(int rt) { swap(t[rt].ls, t[rt].rs); }

void pushUp(int rt) { t[rt].siz = t[t[rt].ls].siz + t[t[rt].rs].siz + t[rt].cnt; }

void pushDown(int rt) {
    if (rt && t[rt].tag) {
        t[t[rt].ls].tag ^= 1;
        t[t[rt].rs].tag ^= 1;
        reverse(rt);
        t[rt].tag = 0;
    }
}

int identify(int rt) { return t[t[rt].fa].rs == rt; }

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
    if (z)
        t[z].ch[y == t[z].rs] = x;
    pushUp(y);
    pushUp(x);
}

void splay(int x, int to = root) {
    to = t[to].fa;
    while (t[x].fa != to) {
        int f = t[x].fa;
        if (t[f].fa == to) {
            rotate(x);
            break;
        }
        if (identify(x) == identify(f)) {
            rotate(f);
            rotate(x);
        } else {
            rotate(x);
            rotate(x);
        }
    }
    if (!to) {
        root = x;
    }
}

int kth(int k) {
    int rt = root;
    while (rt) {
        pushDown(rt);
        if (t[rt].ls && t[t[rt].ls].siz >= k) {
            rt = t[rt].ls;
        }
        else {
            k  -= t[t[rt].ls].siz + t[rt].cnt;
            if (k <= 0) return rt;
            rt = t[rt].rs;
        }
    }
    return 0;
}

int n, m;

void build(int &rt, int l, int r) {
    if (!rt) {
        rt = ++cnt;
    }
    int mid = (l + r) >> 1;
    t[rt].val = mid;
    t[rt].cnt = 1;
    if (l < mid) {
        build(t[rt].ls, l, mid - 1);
        t[t[rt].ls].fa = rt;
    }
    if (r > mid) {
        build(t[rt].rs, mid + 1, r);
        t[t[rt].rs].fa = rt;
    }
    pushUp(rt);
}

void reverse(int l, int r) {
    if (l == 1) {
        if (r == n) {
            t[root].tag ^= 1;
            return;
        } else {
            splay(kth(r + 1));
            t[t[root].ls].tag ^= 1;
            return;
        }
    } else {
        if (r == n) {
            splay(kth(l - 1));
            t[t[root].rs].tag ^= 1;
            return;
        }
    }
    splay(kth(l - 1));
    splay(kth(r + 1), t[root].rs);
    t[t[t[root].rs].ls].tag ^= 1;
    return;
}

void dfs(int rt) {
    if (!rt) return;
    pushDown(rt);
    dfs(t[rt].ls);
    cout << t[rt].val << ' ';
    dfs(t[rt].rs);
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    build(root, 1, n);
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }
    dfs(root);
    cout << endl;
    return 0;
}