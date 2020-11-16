#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int a, b;

int main() {
	cin >> a >> b;
	cout << gcd(a, b) << endl;
	return 0;
}