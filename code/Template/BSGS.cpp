#include <bits/stdc++.h>

using namespace std;

#define int long long

int p, a, b, u;
unordered_map<int, int> m;

inline int qpow(int x, int p, int m) {
	int ans = 1;
	int base = x;
	while (p) {
		if (p & 1) {
			ans = (ans * base) % m;
		}
		base = (base * base) % m;
		p >>= 1;
	}
	return ans;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> p >> a >> b;
	if (a % p == 0) {
		cout << "no solution" << endl;
		return 0;
	}
	u = ceil(sqrt(p));
	for (int i = 0, x = b; i <= u; ++i, x = (x * a) % p) {
		m[x] = i;
	}
	for (int i = 1, t = qpow(a, u, p), x = t; i <= u; ++i, x = (x * t) % p) {
		if (m.count(x)) {
			cout << i * u - m[x] << endl;
			return 0;
		}
	}
	cout << "no solution" << endl;
	return 0;
}