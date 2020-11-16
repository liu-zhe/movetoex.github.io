#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAXN 500005

set<int> block[MAXN];

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
		block[x].insert(a[i]);
	}
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
	int ans = (1 << 31);
	if (idx[l] == idx[r]) {
		for (int i = l; i <= r; ++i) {
			if (a[i] + tag[idx[i]] < x) {
				ans = max(ans, a[i] + tag[idx[i]]);
			}
		}
		return ans == (1 << 31) ? -1 : ans;
	}
	for (int i = l; idx[i] == idx[l]; ++i) {
		if (a[i] + tag[idx[i]] < x) {
			ans = max(ans, a[i] + tag[idx[i]]);
		}
	}
	for (int i = idx[l] + 1; i < idx[r]; ++i) {
		set<int>::iterator it = block[i].lower_bound(x - tag[i]);
        --it;
		if (*it + tag[i] >= x) continue;
		ans = max(ans, *it + tag[i]);
	}
	for (int i = r; idx[i] == idx[r]; --i) {
		if (a[i] + tag[idx[i]] < x) {
			ans = max(ans, a[i] + tag[idx[i]]);
		}
	}
	return ans == (1 << 31) ? -1 : ans;
}

int main() {
	cin >> n;
	siz = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		idx[i] = (i - 1) / siz + 1;
		block[idx[i]].insert(a[i]);
		if (idx[i] != idx[i - 1]) {
			l[idx[i]] = i;
		}
		r[idx[i]] = i;
		cnt		  = max(cnt, idx[i]);
	}
	for (int i = 1; i <= n; ++i) {
		int opt, x, y, z;
		cin >> opt >> x >> y >> z;
		if (opt == 1) {
			cout << query(x, y, z) << endl;
		} else {
			add(x, y, z);
		}
	}
	return 0;
}