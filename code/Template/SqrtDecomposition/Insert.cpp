#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAXN 100005

vector<int> blocks[MAXN];
int n;
int idx[MAXN];
int siz;

vector<int>::iterator iterOf(int x) {
    --x;
    int ans = 1;
    while (blocks[ans].size() <= x) {
        x -= blocks[ans].size();
        ++ans;
    }
    return blocks[ans].begin() + x;
}

int blockOf(int x) {
    int ans = 1;
    while (blocks[ans].size() < x) {
        x -= blocks[ans].size();
        ++ans;
    }
    return ans;
}

int query(int x) {
    return *iterOf(x);
}

void insert(int p, int x) {
    int i = blockOf(p);
    blocks[i].insert(iterOf(p), x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    siz = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        int idx = (i - 1) / siz + 1;
        int x;
        cin >> x;
        blocks[idx].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        int opt, x, y, z;
        cin >> opt >> x >> y >> z;
        if (opt == 0) {
            insert(x, y);
        }
        else {
            cout << query(y) << endl;
        }
    }
    return 0;
}