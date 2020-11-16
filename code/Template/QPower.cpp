#include <iostream>
#include <cmath>

using namespace std;

int qpow(int a, int b, int p) {
    int ans = 1, tmp = a;
    while(b) {
        if (b & 1) ans = (((long long int)ans * tmp % p));
        tmp = tmp * tmp % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    int a, b, p;
    cin >> a >> b >> p;
    cout << qpow(a, b, p) << endl;
    return 0;
}