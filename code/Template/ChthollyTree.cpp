#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long
#define mul(x, y, m) (((x % m) * (y % m)) % m)

struct Node {
    int l, r;
    mutable int val;
    Node(int l = 0, int r = 0, int v = 0) : l(l), r(r), val(v) {}
    bool operator < (const Node& rv) const {
        return l < rv.l;
    }
};

typedef set<Node>::iterator Iter;

int n, m;
set<Node> t;
int a[100005];
int seed;
int vmax;

int qpow(int x, int p, int m) {
    int ans = 1;
    int base = x;
    while (p) {
        if (p & 1) ans = (ans * base) % m;
        base = (base * base) % m;
        p >>= 1;
    }
    return ans;
}

int rnd() {
    int ans = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ans;
}

Iter split(int p) {
    Iter it = t.lower_bound(Node(p));
    if (it != t.end() && it->l == p) {
        return it;
    }
    --it;
    int l = it->l, r = it->r, val = it->val;
    t.erase(it);
    t.insert(Node(l, p - 1, val));
    return t.insert(Node(p, r, val)).first;
}

void assign(int l, int r, int v) {
    Iter end = split(r + 1);
    Iter begin = split(l);
    t.erase(begin, end);
    t.insert(Node(l, r, v));
}

void add(int l, int r, int k) {
    Iter end = split(r + 1);
    Iter begin = split(l);
    for (Iter it = begin; it != end; ++it) {
        it->val += k;
    }
}

int kth(int l, int r, int k) {
    vector<pair<int, int> > v;
    Iter end = split(r + 1);
    Iter begin = split(l);
    for (Iter it = begin; it != end; ++it) {
        v.push_back(make_pair(it->val, it->r - it->l + 1));
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        k -= v[i].second;
        if (k <= 0) return v[i].first;
    }
    return -1;
}

int power(int l, int r, int k, int mod) {
    Iter end = split(r + 1);
    Iter begin = split(l);
    int ans = 0;
    for (Iter it = begin; it != end; ++it) {
        ans = (ans + mul(qpow(it->val % mod, k, mod), it->r - it->l + 1, mod)) % mod;
    }
    return ans % mod;
}

signed main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
		t.insert(Node(i, i, a[i]));
    }
    for (int i = 1; i <= m; ++i) {
        int opt = (rnd() % 4) + 1, l = (rnd() % n) + 1, r = (rnd() % n) + 1, x, y;
        if (l > r) swap(l, r);
		if (opt == 3) x = (rnd() % (r - l + 1)) + 1;
		else x = (rnd() % vmax) + 1;
		if (opt == 4) y = (rnd() % vmax) + 1;

        if (opt == 1) {
            add(l, r, x);
        }
        else if (opt == 2) {
            assign(l, r, x);
        }
        else if (opt == 3) {
            cout << kth(l, r, x) << endl;
        }
        else {
            cout << power(l, r, x, y) << endl;
        }
    }
    return 0;
}