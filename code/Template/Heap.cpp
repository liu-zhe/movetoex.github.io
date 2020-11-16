#include <bits/stdc++.h>

using namespace std;

template <typename T, unsigned MaxSize>
class Heap {

private:
	int size;
	T h[MaxSize << 1 | 1];

public:
	Heap() {}
	~Heap() {}
	void push(T x) {
		h[++size] = x;
		int i = size, j = i >> 1;
		while (h[i] < h[j] && i) {
			swap(h[j], h[i]);
			i = j, j >>= 1;
		}
	}
	T top() {
		return h[1];
	}
	void pop() {
		h[1] = h[size--];
		int node = 1, ls = node << 1, rs = node << 1 | 1;
		while ((h[ls] < h[node] || h[rs] < h[node]) && ls <= size) {
			int p = h[ls] < h[rs] ? ls : rs;
			swap(h[node], h[p]);
			node = p, ls = node << 1, rs = ls | 1;
		}
	}
	bool empty() {
		return size == 0;
	}
};

int n;
Heap<int, 1001> h;

int main() {
	cin >> n;
	for (int i = 1, tmp = 0; i <= n; ++i) {
		cin >> tmp;
		h.push(tmp);
	}
	while (!h.empty()) {
		cout << h.top() << ' ';
		h.pop();
	}
	cout << endl;
	return 0;
}