struct treap {
#define N 700010
	int ch[N][2], w[N], s[N], p[N], rt, cnt;
#define lc ch[x][0]
#define rc ch[x][1]
	void rotate(int &x, int d) {
		int k		 = ch[x][d ^ 1];
		ch[x][d ^ 1] = ch[k][d];
		ch[k][d]	 = x;
		pushup(x);
		pushup(k);
		x = k;
	}
	void ins(int &x, int k) {
		if (!x) {
			x	= cnt++;
			w[x] = k;
			p[x] = rand();
			lc = rc = 0;
			s[x]	= 1;
		} else {
			int d = k < w[x], &u = ch[x][d];
			ins(u, k);
			if (p[u] > p[x]) rotate(x, d ^ 1);
			pushup(x);
		}
	}
	void del(int &x, int k) {
		if (w[x] == k) {
			if (!lc)
				x = rc;
			else if (!rc)
				x = lc;
			else {
				int d = p[lc] > p[rc];
				rotate(x, d);
				del(ch[x][d], k);
			}
		} else {
			int d = k < w[x];
			del(ch[x][d], k);
		}
		pushup(x);
	}
	int rank(int x, int k) {
		if (!x) return 0;
		if (k <= w[x]) return rank(rc, k);
		if (k > w[x]) return rank(lc, k) + s[rc] + 1;
	}
	int kth(int x, int k) {
		int d = k - s[rc];
		if (d == 1) return w[x];
		if (d > 1)
			return kth(lc, d - 1);
		else
			return kth(rc, k);
	}
	void init() {
		s[0] = 0;
		rt   = 0;
		cnt  = 1;
	}
	inline int pushup(int x) {
		if (x) s[x] = s[lc] + s[rc] + 1;
	}
	int pred(int x, int y, int k) {
		if (!x) return w[y];
		if (w[x] <= k)
			return pred(lc, y, k);
		else
			return pred(rc, x, k);
	}
	int succ(int x, int y, int k) {
		if (!x) return w[y];
		if (w[x] >= k)
			return succ(rc, y, k);
		else
			return succ(lc, x, k);
	}
}
