#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 500005

vector<int> block[MAXN];
int idx[MAXN];
int siz;
int a[MAXN];
int tag[MAXN];
int l[MAXN];
int r[MAXN];
int cnt;
int n;

void reset(int x) {
    block[x].clear();
    for (int i = l[x]; i <= r[x]; ++i) {
        block[x].push_back(a[i]);
    }
    sort(block[x].begin(), block[x].end());
}

void add(int l, int r, int k) {
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            a[i] += k;
        }
        reset(idx[l]);
        return;
    }
    for (int i = l; idx[i] == idx[l]; ++i) {
        a[i] += k;
    }
    reset(idx[l]);
    for (int i = idx[l] + 1; i < idx[r]; ++i) {
        tag[i] += k;
    }
    for (int i = r; idx[i] == idx[r]; --i) {
        a[i] += k;
    }
    reset(idx[r]);
}

int query(int l, int r, int x) {
    int ans = 0;
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            if (a[i] + tag[idx[i]] < x) {
                ++ans;
            }
        }
        return ans;
    }
    for (int i = l; idx[i] == idx[l]; ++i) {
        if (a[i] + tag[idx[i]] < x) {
            ++ans;
        }
    }
    for (int i = idx[l] + 1; i < idx[r]; ++i) {
        ans += lower_bound(block[i].begin(), block[i].end(), x - tag[i]) - block[i].begin();
    }
    for (int i = r; idx[i] == idx[r]; --i) {
        if (a[i] + tag[idx[i]] < x) {
            ++ans;
        }
    }
    return ans;
}

int main() {
    cin >> n;
    siz = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        idx[i] = (i - 1) / siz + 1;
        block[idx[i]].push_back(a[i]);
        if (idx[i] != idx[i - 1]) {
            l[idx[i]] = i;
        }
        r[idx[i]] = i;
        cnt = max(cnt, idx[i]);
    }
    for (int i = 1; i <= cnt; ++i) {
        sort(block[i].begin(), block[i].end());
    }
    for (int i = 1; i <= n; ++i) {
        int opt, x, y, z;
        cin >> opt >> x >> y >> z;
        if (opt == 1) {
            cout << query(x, y, z * z) << endl;
        }
        else {
            add(x, y, z);
        }
    }
    return 0;
}