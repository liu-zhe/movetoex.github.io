#include <iostream>
#include <cstring>

using namespace std;

int iPrimesCount = 0;
bool bIsPrime[1000000001] = { 0 };
int n, m;

void EulerSieve(int n) {
	for (int i = 2; i <= n; ++i) bIsPrime[i] = 1;
	for (int i = 2; i <= n; i++) {
		if (bIsPrime[i]){
			for (int j = i * i; j <= n; j += i) {
				bIsPrime[j] = 0;
			}
		}
	}
}

int main() {
    int l, r, ans = 0;
    cin >> n >> m;
    EulerSieve(m);
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        if (l < 1 || l > m || r < 1 || r > m) {
            cout << "Crossing the line" << endl;
        }
        else {
            for (int j = l; j <= r; ++j) {
                if (bIsPrime[j]) ++ans;
            }
            cout << ans << endl;
            ans = 0;
        }
    }
    return 0;
}