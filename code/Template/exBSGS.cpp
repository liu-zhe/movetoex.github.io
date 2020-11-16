#include <bits/stdc++.h>

using namespace std;

#define int long long

int p, a, b;

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

void exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, x, y);
	int t = x;
	x	  = y;
	y	  = t - a / b * y;
}

inline int inv(int a, int p) {
	int x, y;
	exgcd(a, p, x, y);
	return (x + p) % p;
}

inline int qpow(int x, int p, int m) {
	int ans	 = 1;
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

inline int BSGS(int a, int b, int p) {
	if (a % p == 0) return -1;
	unordered_map<int, int> m;
	int u = ceil(sqrt(p));
	for (int i = 0, x = b; i <= u; ++i, x = (x * a) % p) {
		m[x] = i;
	}
	for (int i = 1, t = qpow(a, u, p), x = t; i <= u; ++i, x = (x * t) % p) {
		if (m.count(x)) {
			return i * u - m[x];
		}
	}
	return -1;
}

inline int exBSGS(int a, int b, int p) {
	if (b == 1 || p == 1) return 0;
	int d = 0, k = 0, pd = 1;
	while ((d = gcd(a, p)) != 1) {
		if (b % d) return -1;
		++k;
		b /= d;
		p /= d;
		pd = pd * (a / d) % p;
		if (pd == b) return k;
	}
	int ans = BSGS(a, b * inv(pd, p) % p, p);
	return ans == -1 ? -1 : ans + k;
}

signed main() {
	ios::sync_with_stdio(false);
	while (cin >> a >> p >> b && a && b && p) {
		int ans = exBSGS(a % p, b % p, p);
		if (ans == -1) {
			cout << "No Solution" << endl;
		} else {
			cout << ans << endl;
		}
	}
	return 0;
}