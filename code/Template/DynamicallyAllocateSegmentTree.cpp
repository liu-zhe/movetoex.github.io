#include <iostream>

using namespace std;

struct Node {

	int l, r;
	int val;
	Node *ls, *rs;

	Node(int l = 0, int r = 0, int v = 0) : l(l), r(r), val(v), ls(NULL), rs(NULL) {}

	void pushUp() {
		val = 0;
		if (ls) val += ls->val;
		if (rs) val += rs->val;
	}

	void update(int p, int k) {
		if (l == p && r == p) {
			val += k;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) {
			if (!ls) {
				ls = new Node(l, mid);
			}
			ls->update(p, k);
		} else {
			if (!rs) {
				rs = new Node(mid + 1, r);
			}
			rs->update(p, k);
		}
		pushUp();
	}

	int query(int l, int r) {
		if (this->l >= l && this->r <= r) {
			return val;
		}
		int ans = 0;
		int mid = (this->l + this->r) >> 1;
		if (l <= mid && ls) {
			ans += ls->query(l, r);
		}
		if (r > mid && rs) {
			ans += rs->query(l, r);
		}
		return ans;
	}
};

Node *merge(Node *lv, Node *rv) {
	if (!lv && !rv) {
		return NULL;
	}
	if (!lv || !rv) {
		return new Node(lv ? *lv : *rv);
	}
	Node *rt = new Node(lv->l, lv->r);
	if (lv->l == lv->r) {
		rt->val = lv->val + rv->val;
		return rt;
	}
	int mid = (lv->l + lv->r) >> 1;
	rt->ls = merge(lv->ls, rv->ls);
	rt->rs = merge(lv->rs, rv->rs);
	rt->pushUp();
	return rt;
}

Node *split(Node *&u, int l, int r) {
	if (!u || u->r < l || u->l > r) {
		return NULL;
	}
	Node *rt;
	if (u->l >= l && u->r <= r) {
		rt = new Node(*u);
		u = NULL;
		return rt;
	}
	rt = new Node(u->l, u->r);
	rt->ls = split(u->ls, l, r);
	rt->rs = split(u->rs, l, r);
	rt->pushUp();
	u->pushUp();
	return rt;
}

Node *root[3];
int n;
int a[1001];

int main() {
	cin >> n;
	root[0] = new Node(1, n);
	root[1] = new Node(1, n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		root[0]->update(a[i], 1);
	}
	root[1] = split(root[0], 1, 5);
	for (int i = 1; i <= n; ++i) {
		cout << root[1]->query(i, i) << endl;
	}
	return 0;
}