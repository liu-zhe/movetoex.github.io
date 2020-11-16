#include <cmath>
#include <iostream>


// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#define MAXN 500005

int n;
int a[MAXN];
int block[MAXN];
int siz;
int l[MAXN];
int r[MAXN];
int idx[MAXN];
int max[MAXN];

void pushUp(int x) {
	block[x] = 0;
	max[x]	 = 0;
	for (int i = l[x]; i <= r[x]; ++i) {
		block[x] += a[i];
		max[x] = std::max(max[x], a[i]);
	}
}

void sqrt(int l, int r) {
	if (idx[l] == idx[r]) {
		if (max[idx[l]] > 1) {
			for (int i = l; i <= r; ++i) {
				a[i] = sqrt(a[i]);
			}
			pushUp(idx[l]);
		}
		return;
	}
	if (max[idx[l]] > 1) {
		for (int i = l; idx[i] == idx[l]; ++i) {
			a[i] = sqrt(a[i]);
		}
		pushUp(idx[l]);
	}
	for (int i = idx[l] + 1; i < idx[r]; ++i) {
		if (max[i] > 1) {
			for (int j = ::l[i]; j <= ::r[i]; ++j) {
				a[j] = sqrt(a[j]);
			}
			pushUp(i);
		}
	}
	if (max[idx[r]] > 1) {
		for (int i = r; idx[i] == idx[r]; --i) {
			a[i] = sqrt(a[i]);
		}
		pushUp(idx[r]);
	}
}

int query(int l, int r) {
	int ans = 0;
    if (idx[l] == idx[r]) {
        for (int i = l; i <= r; ++i) {
            ans += a[i];
        }
        return ans;
    }
	for (int i = l; idx[i] == idx[l]; ++i) {
		ans += a[i];
	}
	for (int i = idx[l] + 1; i < idx[r]; ++i) {
		ans += block[i];
	}
	for (int i = r; idx[i] == idx[r]; --i) {
		ans += a[i];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	siz = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		idx[i] = (i - 1) / siz + 1;
		if (idx[i - 1] != idx[i]) {
			l[idx[i]] = i;
		}
		r[idx[i]] = i;
		block[idx[i]] += a[i];
		max[idx[i]] = std::max(max[idx[i]], a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		int opt, x, y, z;
		cin >> opt >> x >> y >> z;
		if (opt == 0) {
			sqrt(x, y);
		} else {
			cout << query(x, y) << endl;
		}
	}
	return 0;
}