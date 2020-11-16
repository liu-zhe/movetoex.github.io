#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int next[1000001];
string T, P;

void init(string s) {
	next[0] = 0;
	for (int i = 1, k = 0; i < s.length(); ++i) {
		while (k > 0 && s[i] != s[k]) {
			k = next[k - 1];
		}
		if (s[i] == s[k]) {
			++k;
		}
		next[i] = k;
	}
}

void KMP(string T, string P) {
	int n = T.size(), m = P.size();
	for (int i = 0, j = 0; i < n; ++i) {
		while (j > 0 && P[j] != T[i]) {
			j = next[j - 1];
		}
		if (P[j] == T[i]) {
			++j;
		}
		if (j == m) {
			j = next[j - 1];
			cout << i - m + 2 << endl;
		}
	}
}

int main() {
	cin >> T >> P;
	init(P);
	KMP(T, P);
	for (int i = 0; i < P.size(); ++i) {
		cout << next[i] << ' ';
	}
	cout << endl;
	return 0;
}