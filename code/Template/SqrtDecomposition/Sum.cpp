#include <iostream>
#include <cmath>

using namespace std;

#define MAXN 500005

int n;
int block[MAXN];
int siz;
int tag[MAXN];
int a[MAXN];
int idx[MAXN];

void add(int l, int r, int k) {
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            a[i] += k;
            block[idx[i]] += k;
        }
        return;
    }
    for (int i = l; idx[i] == idx[l]; ++i) {
        block[idx[i]] += k;
        a[i] += k;
    }
    for (int i = idx[l] + 1; i < idx[r]; ++i) {
        block[i] += siz * k;
        tag[i] += k;
    }
    for (int i = r; idx[i] == idx[r]; --i) {
        block[idx[i]] += k;
        a[i] += k;
    }
}

int query(int x) {
    return tag[idx[x]] + a[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    siz = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        idx[i] = (i - 1) / siz + 1;
    }
    for (int i = 1; i <= n; ++i) {
        int opt, x, y, z;
        cin >> opt >> x >> y >> z;
        if (opt == 0) {
            add(x, y, z);
        }
        else {
            cout << query(y) << endl;
        }
    }
    return 0;
}