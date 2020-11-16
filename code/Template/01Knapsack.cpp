#include <iostream>
#include <algorithm>

using namespace std;

int ts, m;
int t[101], v[101];
int dp[101][1001];

int main() {
	cin >> ts >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> t[i] >> v[i];
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = ts; j >= 0; --j) {
			dp[i][j] = ((j >= t[i]) ? (max(dp[i - 1][j - t[i]] + v[i], dp[i - 1][j])) : dp[i - 1][j]);
		}
	}
	cout << dp[m][ts] << endl;
	return 0;
}