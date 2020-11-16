#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 200005
#define MAXM 200005

struct Node {
    int l, r;
    int val;
    int ls, rs;
    Node operator = (Node& rv) {
        val = rv.val;
        ls = rv.ls;
        rs = rv.rs;
        l = rv.l;
        r = rv.r;
        return *this;
    }
};

struct Data {
    int val;
    int idx;
};

int n, m, q;
Node t[MAXN << 8 | 15];
int cnt;
int root[MAXM];
int a[MAXN];
int b[MAXN];

inline int newNode() {
    return ++cnt;
}

inline int newNode(Node& rt) {
    t[++cnt] = rt;
    return cnt;
}

void build(int rt, int l, int r) {
    t[rt].l = l, t[rt].r = r;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    t[rt].ls = newNode();
    t[rt].rs = newNode();
    build(t[rt].ls, l, mid);
    build(t[rt].rs, mid + 1, r);
}

int add(int rt, int p, int k) {
    rt = newNode(t[rt]);
    t[rt].val += k;
    if (t[rt].l == p && t[rt].r == p) {
        return rt;
    }
    int mid = (t[rt].l + t[rt].r) >> 1;
    if (p <= mid) t[rt].ls = add(t[rt].ls, p, k);
    else t[rt].rs = add(t[rt].rs, p, k);
    return rt;
}

int query(int u, int v, int k) {
    if (t[u].l == t[u].r) return t[u].l;
    int x = t[t[v].ls].val - t[t[u].ls].val;
    if (x >= k) return query(t[u].ls, t[v].ls, k);
    else return query(t[u].rs, t[v].rs, k - x);
}

int main() {
#ifndef ONLINE_JUDGE
    FILE* fp;
    freopen_s(&fp, "9.in", "r", stdin);
    freopen_s(&fp, "test.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    root[0] = newNode();
    build(root[0], 1, m);
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
        root[i] = add(root[i - 1], a[i], 1);
    }
    for (int i = 1; i <= q; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        cout << b[query(root[x - 1], root[y], k)] << endl;
    }
    return 0;
}