#include <iostream>
#include <cmath>

#define int long long

using namespace std;

#define MAXN 500005
// #define MAXB 5005

int n;
int block[MAXN];
int siz;
int idx[MAXN];
int tag[MAXN];
int a[MAXN];

void add(int l, int r, int k) {
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            a[i] += k;
            block[idx[i]] += k;
        }
        return;
    }
    for (int i = l; idx[i] == idx[l]; ++i) {
        a[i] += k;
        block[idx[i]] += k;
    }
    for (int i = idx[l] + 1; i < idx[r]; ++i) {
        tag[i] += k;
        block[i] += siz * k;
    }
    for (int i = r; idx[i] == idx[r]; --i) {
        a[i] += k;
        block[idx[i]] += k;
    }
}

int query(int l, int r, int mod) {
    int ans = 0;
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            ans = (ans + a[i] + tag[idx[i]]) % mod;
        }
        return ans;
    }
    for (int i = l; idx[i] == idx[l]; ++i) {
        ans = (ans + a[i] + tag[idx[i]]) % mod;
    }
    for (int i = idx[l] + 1; i < idx[r]; ++i) {
        ans = (ans + block[i]) % mod;
    }
    for (int i = r; idx[i] == idx[r]; --i) {
        ans = (ans + a[i] + tag[idx[i]]) % mod;
    }
    return ans;
}  

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    siz = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        idx[i] = (i - 1) / siz + 1;
        block[idx[i]] += a[i];
    }
    for (int i = 1; i <= n; ++i) {
        int opt, x, y, z;
        cin >> opt >> x >> y >> z;
        if (opt == 0) {
            add(x, y, z);
        }
        else {
            cout << query(x, y, z + 1) << endl;
        }
    }
    return 0;
}